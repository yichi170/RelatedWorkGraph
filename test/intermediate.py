import os
import sys
import time
import json
import paperpy
import nodepy as ndp

def getInput():
    # get input from the terminal 
    mode = input("Input the mode (citations/[references]): ")
    maxbranch = input("Input the maximum branches of node [10]: ")
    maxnode = input("Input the maximum number of node [50]: ")
    title = input("Input the title of the paper [off policy actor critic 2012]: ").replace(' ', '+')

    # for fast test
    if title == "":
        title = "off+policy+actor+critic+2012"

    if maxnode == "":
        maxnode = 50
    else:
        maxnode = int(maxnode)

    if maxbranch == "":
        maxbranch = 10
    else:
        maxbranch = int(maxbranch)

    # get the relationship of papers
    begin = time.perf_counter_ns()
    paper_list, paper_id_list, paper_relation = paperpy.get_relation(mode, maxbranch, maxnode, title)
    end = time.perf_counter_ns()

    print(f"Time of getting the relationship of the nodes: {(end - begin) / 1e9} * 1e-9 s")

    return paper_list, paper_id_list, paper_relation

def main(rel_file, pos_file):
    paper_list, paper_id_list, paper_relation = getInput()
    
    begin = time.perf_counter_ns()
    
    # construct the system, pass the needed parameters, and get the position of the nodes
    system = ndp.NodeSystem(len(paper_id_list), 10000, 10000, 5e3, paper_relation)
    system.run_times(100000)
    position = system.getPos()
    
    end = time.perf_counter_ns()

    print(f"Time of calculating the position of the nodes: {(end - begin) / 1e9} * 1e-9 s")

    begin = time.perf_counter_ns()
    
    with open(rel_file, 'w') as f1, open(pos_file, 'w') as f2, open(info_file, 'w') as f3:
        f1.write('\n'.join(f"{src} {trg}" for (src, trg) in paper_relation))
        f2.write('\n'.join(f"{x} {y}" for (x, y) in position))
        json.dump(paper_list, f3)

    end = time.perf_counter_ns()
    print(f"Time of writing the information into files: {(end - begin) / 1e9} * 1e-9 s")

if __name__ == '__main__':
    script, rel_file, pos_file, info_file = sys.argv
    main(rel_file, pos_file)
