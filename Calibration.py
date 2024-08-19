# importing the useful packages
import numpy as np
import os
import matplotlib.pyplot as plt
import pandas as pd
from scipy import optimize
import function as f
from scipy.signal import find_peaks



class Calib_position:

    "This class should perform the first step of calibration for the 16 strip detector"

    def __init__(self, x_label, y_label):
        "Constructor"
        self.xlabel=x_label
        self.ylabel=y_label


    def read_data(self, filename):
        "Defining directories and creating filepath to open file, connected to read_hdat"
        work_dir = os.getcwd()
        data_dir = os.path.join(work_dir, "Uncalib_position")

        filepath = os.path.join(data_dir,filename)
        self.name=filename
        self.read_hdat(filepath)


    def read_hdat(self, filepath):
        "This function opens file and creates data frame"
        my_df = pd.read_csv(filepath, sep="\t", header=1) 
        self.position = my_df[self.xlabel].to_numpy()
        self.energy = my_df[self.ylabel].to_numpy()
        self.content = my_df['Content']


    def plot_hist(self, strip_number):
        "This function plots a 2-d histogram of energy vs. strip position"
        # selecting only the relevant bins
        index = np.where(self.content!=0)
        self.selected_energy = self.energy[index]
        self.selected_position = self.position[index]
        self.selected_content = self.content[index[0]]

        # Determine the number of unique bins in x and y
        x_bins = np.unique(self.selected_position)
        y_bins = np.unique(self.selected_energy)

        # Original number of bins
        original_x_bins = len(x_bins)
        original_y_bins = len(y_bins)

        # Define the desired number of bins
        new_x_bins = 26  # Modify as needed
        new_y_bins = 200  # Modify as needed

        # Calculate the new bin edges
        self.x_edges = np.linspace(x_bins.min(), x_bins.max(), new_x_bins + 1)
        self.y_edges = np.linspace(y_bins.min(), y_bins.max(), new_y_bins + 1)

        # Re-bin the counts
        self.counts_2d, _, _ = np.histogram2d(self.selected_position, self.selected_energy, bins=[self.x_edges, self.y_edges], weights=self.selected_content)

        # Plot the re-binned 2D histogram using imshow
        plt.figure(figsize=(10,6))
        plt.imshow(self.counts_2d.T, origin='lower', extent=[x_bins.min(), x_bins.max(), y_bins.min(), y_bins.max()], aspect='auto', cmap='twilight')
        plt.colorbar(label='Counts')
        plt.xlabel('Position')
        plt.ylabel('Energy')
        plt.title("Histogram of Energy vs Uncalib Position strip %s" % strip_number, fontsize=20)


    def plot_data(self, strip_number, plot=False):
        "This function selects the coordinates of the bin tip with most counts and plots them"
        # Find the indices where the bin counts are greater than 4 (number might change depending on data, check with the hist)
        indices = np.where(self.counts_2d > 10)

        # Extract the bin edges corresponding to these indices
        x_coords = (self.x_edges[indices[0]] + self.x_edges[indices[0] + 1]) / 2
        y_coords = (self.y_edges[indices[1]] + self.y_edges[indices[1] + 1]) / 2

        xx = []
        yy = []

        # Print or store the coordinates
        for x, y in zip(x_coords, y_coords):
            #print(f"X: {x}, Y: {y}")
            xx.append(x)
            yy.append(y)

        self.yy = np.array(yy)
        self.xx = np.array(xx)

        if plot==True:

            plt.figure(figsize=(10,8))
            plt.scatter(xx,yy, label='Data')
            plt.xlabel("Strip position", fontsize=15)
            plt.ylabel("Channel", fontsize=15)
            plt.title("Scatter plot of Energy vs Calib Position strip %s" % strip_number, fontsize=20)
            plt.grid(True)


    def fit_data(self, lower_bound, upper_bound, strip_number):
        "This function fits the three separate curves"
        cond1 = self.yy<lower_bound # condition for first curve
        cond2_a = self.yy>lower_bound # condition for second curve
        cond2_b = self.yy<upper_bound # condition for second curve
        cond3 = self.yy>upper_bound # condition for third curve

        # first curve
        index1 = np.where(cond1)
        self.yy1 = self.yy[index1]
        xx1 = self.xx[index1]

        # second curve
        index2 = np.where(np.logical_and(cond2_a, cond2_b))
        self.yy2 = self.yy[index2]
        xx2 = self.xx[index2]

        # third curve
        index3 = np.where(cond3)
        self.yy3 = self.yy[index3]
        xx3 = self.xx[index3]

        # trying to fit all three
        self.fit_model = f.parabola
        self.popt, self.pcov = optimize.curve_fit(self.fit_model, xx1, self.yy1)
        self.popt2, self.pcov2 = optimize.curve_fit(self.fit_model, xx2, self.yy2)
        self.popt3, self.pcov3 = optimize.curve_fit(self.fit_model, xx3, self.yy3)

        # plotting the fit for the first curve

        plt.figure(figsize=(10,8))
        plt.scatter(self.xx,self.yy, label='Data')
        plt.plot(xx1, self.fit_model(xx1, *self.popt), "r-", label='fit')

        plt.xlabel("Strip position", fontsize=15)
        plt.ylabel("Channel", fontsize=15)
        plt.title("Scatter plot of Energy vs Calib Position strip %s" % strip_number, fontsize=20)

        # plotting the fit for the second curve
        plt.plot(xx2, self.fit_model(xx2, *self.popt2), "r-")

        # plotting the fit for the third curve
        plt.plot(xx3, self.fit_model(xx3, *self.popt3), "r-")
        plt.legend(loc='best')
        plt.grid(True)


    def fit_results(self):
        "This function prints the best fit parameters with their error"
        print("a1 =", self.popt[0], "+/-", self.pcov[0,0]**0.5)
        print("b1 =", self.popt[1], "+/-", self.pcov[1,1]**0.5)
        print("c1 =", self.popt[2], "+/-", self.pcov[2,2]**0.5)
        print("a2 =", self.popt2[0], "+/-", self.pcov2[0,0]**0.5)
        print("b2 =", self.popt2[1], "+/-", self.pcov2[1,1]**0.5)
        print("c2 =", self.popt2[2], "+/-", self.pcov2[2,2]**0.5)
        print("a3 =", self.popt3[0], "+/-", self.pcov3[0,0]**0.5)
        print("b3 =", self.popt3[1], "+/-", self.pcov3[1,1]**0.5)
        print("c3 =", self.popt3[2], "+/-", self.pcov3[2,2]**0.5)


    def write_txt(self, output_filename, strip_number):
        "This function writes fit results in a text file"
        self.output_name = output_filename
        work_dir = os.getcwd()
        results_dir = os.path.join(work_dir, 'results')
        output_filepath = os.path.join(results_dir, self.output_name)

        text=open(output_filepath+strip_number+".dat", "w")

        print("# Strip %s fit results" % strip_number, '\n', file=text)
        print(self.popt[0], self.popt[1], self.popt[2] - np.min(self.yy1), file=text)
        print(self.popt2[0], self.popt2[1], self.popt2[2] - np.min(self.yy2), file=text)
        print(self.popt3[0], self.popt3[1], self.popt3[2] - np.min(self.yy3), file=text)

        text.close()


    def plot_calib_hist(self, lower_bound, upper_bound, strip_number):
        "This function subtracts the curve obtained and plot the corrected histogram"
        for jj in range(len(self.selected_energy)-1):
            if self.selected_energy[jj]<lower_bound:
                self.selected_energy[jj] = self.selected_energy[jj] - self.fit_model(self.selected_position[jj], *self.popt) + np.min(self.yy1)
            elif self.selected_energy[jj]>upper_bound:
                self.selected_energy[jj] = self.selected_energy[jj] - self.fit_model(self.selected_position[jj], *self.popt3) + np.min(self.yy2)
            else:
                self.selected_energy[jj] = self.selected_energy[jj] - self.fit_model(self.selected_position[jj], *self.popt2) + np.min(self.yy3)


        # Determine the number of unique bins in x and y
        x_bins = np.unique(self.selected_position)
        y_bins = np.unique(self.selected_energy)

        # Original number of bins
        original_x_bins = len(x_bins)
        original_y_bins = len(y_bins)

        # Define the desired number of bins
        new_x_bins = 26  # Modify as needed
        new_y_bins = 200  # Modify as needed

        # Calculate the new bin edges
        self.x_edges = np.linspace(x_bins.min(), x_bins.max(), new_x_bins + 1)
        self.y_edges = np.linspace(y_bins.min(), y_bins.max(), new_y_bins + 1)

        # Re-bin the counts
        self.counts_2d, _, _ = np.histogram2d(self.selected_position, self.selected_energy, bins=[self.x_edges, self.y_edges], weights=self.selected_content)

        # Plot the re-binned 2D histogram using imshow
        plt.figure(figsize=(10,6))
        plt.imshow(self.counts_2d.T, origin='lower', extent=[x_bins.min(), x_bins.max(), y_bins.min(), y_bins.max()], aspect='auto', cmap='twilight')
        plt.colorbar(label='Counts')
        plt.xlabel('Position')
        plt.ylabel('Energy')
        plt.title("Histogram of Energy vs Calib Position strip %s" % strip_number, fontsize=20)






class Calib_energy:

    "This class should perform the second step of the calibration for the 16 strip"

    def __init__(self, x_label, y_label):
        "Constructor"
        self.xlabel=x_label
        self.ylabel=y_label


    def read_data(self, filename):
        "Defining directories and creating filepath to open file, connected to read_hdat"
        work_dir = os.getcwd()
        data_dir = os.path.join(work_dir, "Uncalib_energy")

        filepath = os.path.join(data_dir,filename)
        self.name=filename
        self.read_hdat(filepath)


    def read_hdat(self, filepath):
        "This function opens file and creates data frame"
        my_df = pd.read_csv(filepath, sep="\t", header=1) 
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
        plt.xlim(3000, 4000)
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

        plt.xlabel("Strip position", fontsize=15)
        plt.ylabel("Channel", fontsize=15)
        plt.title("Plot of position corrected energy strip %s" % strip_number, fontsize=20)
        plt.legend(loc='best')
        plt.grid(True)
        plt.xlim(3100,3900)

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


    def write_txt(self, output_filename, strip_number):
        "This function writes fit results in a text file"
        self.output_name = output_filename
        work_dir = os.getcwd()
        results_dir = os.path.join(work_dir, 'results')
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

    def read_txt(self, filename):
        "This function reads the data from a text file"
        work_dir = os.getcwd()
        data_dir = os.path.join(work_dir, "results")

        filepath = os.path.join(data_dir,filename)
        self.name=filename
        self.channel, self.error = np.loadtxt(filepath, comments='#', unpack=True)


    def plot_errorbar(self, strip_number, plot=True):
    
        "This function plots an errorbar of channel-energy data"
        if plot==True:
            plt.figure(figsize=(10,6))
            plt.errorbar(self.energy, self.channel, yerr=self.error, fmt='.', label='data')
            plt.xlabel('Energy [keV]')
            plt.ylabel('Channel [keV]')
            plt.title('Plot of channel number vs. energy strip %s' % strip_number)
            plt.grid(True)


    def fit_line(self, strip_number, plot=True):

        "This function performs and plot the fit"

        self.fit_model = f.line
        self.popt, self.pcov = optimize.curve_fit(self.fit_model, self.energy, self.channel, sigma=self.error)
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


    def write_txt(self, output_filename, strip_number):
        "This function writes fit results in a text file"
        self.output_name = output_filename
        work_dir = os.getcwd()
        results_dir = os.path.join(work_dir, 'results')
        output_filepath = os.path.join(results_dir, self.output_name)

        text=open(output_filepath+strip_number+".dat", "w")

        print("# Strip %s fit results" % strip_number, '\n', file=text)
        print(self.popt[0], self.popt[1], file=text)


        text.close()
