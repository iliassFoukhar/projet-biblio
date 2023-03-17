import subprocess
from math import ceil
from os import listdir
from os.path import isfile, join

DIRS = ["low-dimensional","large_scale"]
LABELS = ["Low dimensional", "Large Scale"]
PATH = "./instances/"
print("############################################################")
print("Script launching...")
print("Method number 1...")
print("DYNAMIC PROGRAMMING")
print("############################################################")

def run_dp_all_instances():
    for i in range(2):
        current_folder_path = PATH + DIRS[i]
        print("############################################################")
        print("Reading folder: {0}". format(LABELS[i]))
        print("Path of folder: {0}". format(current_folder_path))
        print("############################################################")
        input_files = [f for f in listdir(current_folder_path) if isfile(join(current_folder_path, f))]
        for file in input_files:
            current_file_path = "{0}/{1}".format(current_folder_path, file)
            execution_command = ["./main.exe", current_file_path, "./ResultsDP/{0}".format(file)]
            print("Executing file: ")
            print(current_file_path)
            subprocess.run(execution_command)


def get_obtained_score(output_folder):
    resulting_scores = dict()
    output_files = [f for f in listdir(output_folder) if isfile(join(output_folder, f))]
    for file in output_files:
        file_path = output_folder + "/" + file
        file_opened = open(file_path, 'r')
        lines = file_opened.readlines()
        if len(lines) > 0:
            maximum_value = int(lines[0].strip())
            resulting_scores[file] = maximum_value
    return resulting_scores

def get_optimums():
    optimums = dict()
    l = list()
    for i in range(2):
        current_folder_path = PATH + DIRS[i] + "-optimum"
        optimum_files = [f for f in listdir(current_folder_path) if isfile(join(current_folder_path, f))]
        for file in optimum_files:
            file_path = current_folder_path + "/" + file
            
            l.append(file_path)
            file_opened = open(file_path, "r")
            lines = file_opened.readlines()
            maximum_value = int(ceil(float(lines[0].strip())))
            optimums[file] = maximum_value
    print("Len optimums in function : ", len(optimums.keys()))
    return optimums



def compare_scores(optimums, resulting_scores):
    wrong = 0
    correct = 0
    listy = []
    for file in optimums.keys():
        if resulting_scores[file] == optimums[file]:
            correct += 1
        else:
            listy.append(file)
            wrong += 1

    return [correct, wrong]


run_dp_all_instances()
scoresDP = get_obtained_score("./ResultsDP")
optimums = get_optimums()

results = compare_scores(optimums=optimums, resulting_scores=scoresDP)
print("############################################################")
print("Results : ")
print("Correct answers : ", results[0])
print("Wrong Answers : " , results[1])
print("Accuracy : " , (results[0] / len(optimums)) * 100, '%')
print("Error rate: ", (results[1] / len(optimums)) * 100, '%')
print("############################################################")

