# importing the useful packages
import numpy as np
import os
import matplotlib.pyplot as plt
import pandas as pd
from scipy import optimize

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
        self.position = my_df["# X "].to_numpy()
        self.energy = my_df["Y "].to_numpy()