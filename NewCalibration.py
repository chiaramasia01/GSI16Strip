# importing the useful packages
import numpy as np
import os
import matplotlib.pyplot as plt
import pandas as pd
from scipy import optimize
import function as f
from scipy.signal import find_peaks


# C. Masia
# Summer student program 2024
# any questions or suggestions chiara.masia01@gmail.com



class Calib_position:

    "This class should perform the first step of calibration for the 16 strip detector"

    def __init__(self, x_label, y_label):
        "Constructor"
        self.xlabel=x_label
        self.ylabel=y_label


    def read_data(self, filename):
        "Defining directories and creating filepath to open file, connected to read_hdat"
        work_dir = os.getcwd()

        filepath = os.path.join(work_dir,filename)
        self.name=filename
        self.read_hdat(filepath)


    def read_hdat(self, filepath):
        "This function opens file and creates data frame"
        self.my_df = pd.read_csv(filepath, sep=" ", header=0) 
        self.position = self.my_df[self.xlabel].to_numpy()
        self.energy = self.my_df[self.ylabel].to_numpy()
        self.strip = self.my_df['Stripnum'].to_numpy()


    def plot_hist(self, strip_number):
        "This function plots a 2-d histogram of energy vs. strip position for each single strip"
        # selecting only the data for the single strip

        index = self.my_df['Stripnum'].loc[self.my_df['Stripnum'] == strip_number].index
        self.energy = self.energy[index]
        self.position = self.position[index]


        # Plot the 2D histogram 
        self.energy_sel = self.energy[self.energy!=0] 
        self.position_sel = self.position[self.energy!=0]
        plt.figure(figsize=(10,6))
        ax=plt.gca()
        self.h, self.xedges, self.yedges, _ = plt.hist2d(self.position_sel, self.energy_sel, bins=(42,500), cmap='twilight')
        plt.colorbar(label='Counts')
        plt.xlabel('Position [mm]', fontsize=15)
        plt.ylabel('Channel [arb.un.]', fontsize=15)
        plt.ylim(3000,4000)
        plt.title("Histogram of Energy vs Uncalib Position strip %s" % strip_number, fontsize=20)
        plt.text(0.75, 0.24, 'plutonium-239', transform=ax.transAxes, fontsize=15)
        plt.text(0.74, 0.51, 'americium-241', transform=ax.transAxes, fontsize=15)
        plt.text(0.8, 0.82, 'curium-244', transform=ax.transAxes, fontsize=15)


    def plot_data(self, strip_number, count_threshold, plot=False):  # change from false to true to display the plot
        "This function selects the coordinates of the bins with counts greater than a threshold and plots them"

        # Get the bin centers
        x_centers = (self.xedges[:-1] + self.xedges[1:]) / 2
        y_centers = (self.yedges[:-1] + self.yedges[1:]) / 2

        # Create a meshgrid of bin centers
        selected_x, selected_y = np.meshgrid(x_centers, y_centers, indexing='ij')

        # Find the indices where the bin counts are greater than a threshold
        indices = self.h >= count_threshold

        # Extract the coordinates for the bins that meet the threshold
        selected_x_coords = selected_x[indices]
        selected_y_coords = selected_y[indices]
        selected_counts = self.h[indices]

        # Store the selected coordinates for later use
        
        self.yy = np.array(selected_y_coords)
        self.xx = np.array(selected_x_coords)

        # Output the selected coordinates and their counts
        #for x, y, count in zip(selected_x_coords, selected_y_coords, selected_counts):
            #print(f"Selected bin at (x, y): ({x}, {y}) with counts: {count}")


        # Plot the selected coordinates
        if plot:
            plt.figure(figsize=(10, 8))
            plt.scatter(selected_x_coords, selected_y_coords, c=selected_counts, cmap='viridis', label='Data')
            plt.colorbar(label='Counts')
            plt.xlabel("Strip position [mm]", fontsize=15)
            plt.ylabel("Channel [arb.un.]", fontsize=15)
            plt.title(f"Scatter plot of Energy vs Calib Position strip {strip_number}", fontsize=20)
            plt.grid(True)
            plt.legend()
            plt.show()



    def fit_data(self, strip_number, lower_bound, upper_bound):
        "This function fits the three separate curves"

        cond1 = self.yy<lower_bound # condition for first curve
        cond2_a = self.yy>lower_bound # condition for second curve
        cond2_b = self.yy<upper_bound # condition for second curve
        cond3 = self.yy>upper_bound # condition for third curve

        # first curve
        index1 = np.where(cond1)
        self.yy1 = self.yy[index1]
        self.xx1 = self.xx[index1]

        # second curve
        index2 = np.where(np.logical_and(cond2_a, cond2_b))
        self.yy2 = self.yy[index2]
        self.xx2 = self.xx[index2]

        # third curve
        index3 = np.where(cond3)
        self.yy3 = self.yy[index3]
        self.xx3 = self.xx[index3]


        # trying to fit all three
          
        self.fit_model = f.parabola
        guess = [0.1, -5, 3700]
        self.popt, self.pcov = optimize.curve_fit(self.fit_model, self.xx1, self.yy1, p0=guess)
        self.popt2, self.pcov2 = optimize.curve_fit(self.fit_model, self.xx2, self.yy2, p0=guess)
        

        # plotting the fit for the first curve

        plt.figure(figsize=(10,8))
        plt.scatter(self.xx,self.yy, label='Data')
        plt.plot(self.xx, self.fit_model(self.xx, *self.popt), "r-", label='fit')

        plt.xlabel("Strip position [mm]", fontsize=15)
        plt.ylabel("Channel [arb.un.]", fontsize=15)
        plt.title("Scatter plot of Energy vs Calib Position strip %s" % strip_number, fontsize=20)

        # plotting the fit for the second curve
        plt.plot(self.xx, self.fit_model(self.xx, *self.popt2), "r-")


        plt.legend(loc='best')
        plt.grid(True)

        if len(self.yy3)>3:
            self.popt3, self.pcov3 = optimize.curve_fit(self.fit_model, self.xx3, self.yy3, p0=guess)
            # plotting the fit for the third curve
            plt.plot(self.xx, self.fit_model(self.xx, *self.popt3), "r-")


    def fit_results(self):
        "This function prints the best fit parameters with their error"
        print("a1 =", self.popt[0], "+/-", self.pcov[0,0]**0.5)
        print("b1 =", self.popt[1], "+/-", self.pcov[1,1]**0.5)
        print("c1 =", self.popt[2], "+/-", self.pcov[2,2]**0.5)
        print("a2 =", self.popt2[0], "+/-", self.pcov2[0,0]**0.5)
        print("b2 =", self.popt2[1], "+/-", self.pcov2[1,1]**0.5)
        print("c2 =", self.popt2[2], "+/-", self.pcov2[2,2]**0.5)
        if len(self.yy3)>3:
            print("a3 =", self.popt3[0], "+/-", self.pcov3[0,0]**0.5)
            print("b3 =", self.popt3[1], "+/-", self.pcov3[1,1]**0.5)
            print("c3 =", self.popt3[2], "+/-", self.pcov3[2,2]**0.5)


    def write_txt(self, output_filename, strip_number, energy_1, energy_2, energy_3, sparechip):
        "This function writes fit results in a text file"
        self.output_name = output_filename
        work_dir = os.getcwd()
        results_dir = os.path.join(work_dir, 'results/'+sparechip)
        output_filepath = os.path.join(results_dir, self.output_name)

        text=open(output_filepath+str(strip_number)+".dat", "w")

        print("# Strip %s fit results" % strip_number, '\n', file=text)
        print(self.popt[0], self.popt[1], self.popt[2] - energy_1, file=text)
        print(self.popt2[0], self.popt2[1], self.popt2[2] - energy_2, file=text)
        if len(self.yy3)>3:
            print(self.popt3[0], self.popt3[1], self.popt3[2] - energy_3, file=text)

        text.close()


    def plot_calib_hist(self, lower_bound, upper_bound, strip_number, energy_1, energy_2, energy_3):
        "This function subtracts the curve obtained and plot the corrected histogram"
        if len(self.yy3)<=3:
            self.popt3 = self.popt2

        for jj in range(len(self.energy_sel)-1):
            if self.energy_sel[jj]<lower_bound:
                self.energy_sel[jj] = self.energy_sel[jj] - self.fit_model(self.position_sel[jj], *self.popt) + energy_1
            elif self.energy_sel[jj]>upper_bound:
                self.energy_sel[jj] = self.energy_sel[jj] - self.fit_model(self.position_sel[jj], *self.popt3) + energy_3
            else:
                self.energy_sel[jj] = self.energy_sel[jj] - self.fit_model(self.position_sel[jj], *self.popt2) + energy_2

        plt.figure(figsize=(10,6))
        ax=plt.gca()
        self.h, self.xedges, self.yedges, _ = plt.hist2d(self.position_sel, self.energy_sel, bins=(42,500), cmap='twilight')
        plt.colorbar(label='Counts')
        plt.xlabel('Position [mm]', fontsize=15)
        plt.ylabel('Channel [arb.un.]', fontsize=15)
        plt.ylim(5000,6000)
        plt.title("Histogram of Energy vs Calib Position strip %s" % strip_number, fontsize=20)
        plt.text(0.75, 0.2, 'plutonium-239', transform=ax.transAxes, fontsize=15)
        plt.text(0.74, 0.51, 'americium-241', transform=ax.transAxes, fontsize=15)
        plt.text(0.8, 0.82, 'curium-244', transform=ax.transAxes, fontsize=15)


    def save_hist_data(self, output_filename, strip_number):
        "This function extracts the data from the corrected histogram and saves it in a txt file"
        self.output_name = output_filename
        work_dir = os.getcwd()
        results_dir = os.path.join(work_dir, 'Uncalib_energy')
        output_filepath = os.path.join(results_dir, self.output_name)

        text=open(output_filepath, "w")

        print("# Strip %s balistic calibration results" % strip_number, '\n', file=text)
        print("#energy #content", '\n', file=text)

        # getting bin centers
        ycenters = (self.yedges[:-1] + self.yedges[1:])/2
        
        for jj in range(len(ycenters)):
            print(ycenters[jj], self.h[1][jj], file=text)

        text.close()        



class Calib_energy:

    "This class should perform the second step of the calibration for the 16 strip"

    def __init__(self, x_label, y_label):
        "Constructor"
        self.xlabel=x_label
        self.ylabel=y_label


    def read_data(self, filename, sparechip):
        "Defining directories and creating filepath to open file, connected to read_hdat"
        work_dir = os.getcwd()
        data_dir = os.path.join(work_dir, "Uncalib_energy/"+str(sparechip))

        filepath = os.path.join(data_dir,filename)
        self.name=filename
        self.read_hdat(filepath)


    def read_hdat(self, filepath):
        "This function opens file and creates data frame"
        my_df = pd.read_csv(filepath, sep="\t", header=1, skip_blank_lines=True) 
        self.energy = my_df[self.xlabel].to_numpy()
        self.content = my_df[self.ylabel].to_numpy()

        
    def plot_hist(self, strip_number):
        "This function plots a 1-d histogram of energy"

        # plotting the histogram

        plt.figure(figsize=(10,8))

        plt.bar(self.energy, self.content, width=10)
        plt.xlabel("Channel", fontsize=15)
        plt.ylabel("Content", fontsize=15)
        plt.title("Histogram of position corrected energy strip %s" % strip_number, fontsize=20)
        plt.xlim(5000, 6000)
        plt.grid(True)


    def initial_guess(self,plot=False):
        """Finds peaks and from that creates 
        the initial values for the fit"""
        index,_=find_peaks(self.content,prominence=200)
            
        if plot==True:
            plt.errorbar(self.energy[index],self.content[index],fmt='o', label='peaks', color='orange')

        guess=[0]
        for ii in index:
            guess.append(self.content[ii]) # amplitude
            guess.append(self.energy[ii]) # mean
            guess.append(50) # sigma
        
        return guess


    def fit_gauss(self, strip_number):
        "This function performs a gaussian fit of the data with three gaussians"

        self.fit_model = f.multi_gauss3
        init = self.initial_guess()
        dy = np.ones(len(self.content))*10
        self.popt, self.pcov = optimize.curve_fit(self.fit_model, self.energy, self.content, sigma = dy, p0=init)
        plt.figure(figsize=(10,8))
        plt.bar(self.energy, self.content, width=10, label='data')
        xx = np.linspace(min(self.energy), max(self.energy), 5000)
        plt.plot(xx, self.fit_model(xx, *self.popt), "r-", label='fit')

        plt.xlabel("Strip position [mm]", fontsize=15)
        plt.ylabel("Channel [arb.un.]", fontsize=15)
        plt.title("Plot of position corrected energy strip %s" % strip_number, fontsize=20)
        plt.legend(loc='best')
        plt.grid(True)
        plt.xlim(5000,6000)

        self.fit_results()


    def fit_results(self):
        "This function prints the best fit parameters with their error"
        print("c0 =", self.popt[0], "+/-", self.pcov[0,0]**0.5)
        print("c1 =", self.popt[1], "+/-", self.pcov[1,1]**0.5)
        print("m1 =", self.popt[2], "+/-", self.pcov[2,2]**0.5)
        print("s1 =", self.popt[3], "+/-", self.pcov[3,3]**0.5)
        print("c2 =", self.popt[4], "+/-", self.pcov[4,4]**0.5)
        print("m2 =", self.popt[5], "+/-", self.pcov[5,5]**0.5)
        print("s2 =", self.popt[6], "+/-", self.pcov[6,6]**0.5)
        print("c3 =", self.popt[7], "+/-", self.pcov[7,7]**0.5)
        print("m3 =", self.popt[8], "+/-", self.pcov[8,8]**0.5)
        print("s3 =", self.popt[9], "+/-", self.pcov[9,9]**0.5)


    def write_txt(self, output_filename, strip_number, chipnumber):
        "This function writes fit results in a text file"
        self.output_name = output_filename
        work_dir = os.getcwd()
        results_dir = os.path.join(work_dir, 'results/'+str(chipnumber))
        output_filepath = os.path.join(results_dir, self.output_name)

        text=open(output_filepath+strip_number+".dat", "w")

        print("# Strip %s gauss fit results" % strip_number, '\n', file=text)
        print(self.popt[2], self.pcov[2,2]**0.5, file=text)
        print(self.popt[5], self.pcov[5,5]**0.5, file=text)
        print(self.popt[8], self.pcov[8,8]**0.5, file=text)
        

        text.close()




class Calib_channel:

    " This class should perform the final step of the calibration returning the conversion factor between energy and channel "
    def __init__(self, energy_1, energy_2, energy_3):
        "Constructor, defining the tabulated energies of the three alpha peaks"
        self.energy1 = energy_1
        self.energy2 = energy_2
        self.energy3 = energy_3
        self.energy = np.array([self.energy1, self.energy2, self.energy3])

    def read_txt(self, filename, sparechip):
        "This function reads the data from a text file"
        work_dir = os.getcwd()
        data_dir = os.path.join(work_dir, "results/"+str(sparechip))

        filepath = os.path.join(data_dir,filename)
        self.name=filename
        self.channel, self.error = np.loadtxt(filepath, comments='#', unpack=True)


    def plot_errorbar(self, strip_number, plot=True):
    
        "This function plots an errorbar of channel-energy data"
        if plot==True:
            plt.figure(figsize=(10,6))
            plt.errorbar(self.channel, self.energy, yerr=self.error, fmt='.', label='data')
            plt.ylabel('Energy [keV]')
            plt.xlabel('Channel [arb. un.]')
            plt.title('Plot of energy vs. channel number strip %s' % strip_number)
            plt.grid(True)


    def fit_line(self, strip_number, plot=True):

        "This function performs and plot the fit"

        self.fit_model = f.line
        self.popt, self.pcov = optimize.curve_fit(self.fit_model, self.channel, self.energy, sigma=self.error)
        self.fit_results()
    

        if plot==True:
            self.plot_errorbar(strip_number)
            xx = np.linspace(5100,5900,1000)
            plt.plot(xx, self.fit_model(xx, *self.popt), "r-", label='fit')
            plt.legend()
            plt.grid(True)


    def fit_results(self):
        "This function prints the best fit parameters with their error"

        print("m =", self.popt[0], "+/-", self.pcov[0,0]**0.5)
        print("q =", self.popt[1], "+/-", self.pcov[1,1]**0.5)


    def write_txt(self, output_filename, strip_number, sparechip):
        "This function writes fit results in a text file"
        self.output_name = output_filename
        work_dir = os.getcwd()
        results_dir = os.path.join(work_dir, 'results/'+sparechip)
        output_filepath = os.path.join(results_dir, self.output_name)

        text=open(output_filepath+strip_number+".dat", "w")

        print("# Strip %s fit results" % strip_number, '\n', file=text)
        print(self.popt[0], self.popt[1], file=text)


        text.close()
