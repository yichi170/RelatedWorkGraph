from bs4 import BeautifulSoup
import requests

root = "https://api.semanticscholar.org/graph/v1"

paper_list = []
id_to_index = dict()
index_to_id = dict()
relation_list = []

def get_paper_url(arxiv_id):
    return f"arxiv.org/pdf/{arxiv_id}"

def get_relation(mode, maxbranch, maxnode, title):
    # get Input from console
    if mode != "citations":
        mode = "references"
    if maxbranch <= 0:
        maxbranch = 10
    if maxnode <= 0:
        maxnode = 1000
    
    # Search for this paper
    r = requests.get(root+f"/paper/search?query={title}&fields=title,abstract,url,year,authors,citationCount") # paperID, title
    data = r.json()
    # put the candidate paper into the list [{paper1}, {paper2}]
    # {"paperId": "", "title": ""}
    
    # root paper
    paper_list.append(data['data'][0])
    paper_id_list = [0]

    for i, result in enumerate(paper_list):
        if result["paperId"] == None:
            continue
        fln = requests.get(root + f"/paper/{result['paperId']}/{mode}?fields=title,abstract,url,year,authors,citationCount").json()
        
        length = len(paper_list)
        # print(fln["data"])
        for j, paper in enumerate(fln["data"]):
            if mode == "citations":
                paper = paper["citingPaper"]
            else:
                paper = paper["citedPaper"]
            
            paper_id_list.append(length + j)
            relation_list.append((i, length + j))
            paper_list.append(paper)
            if j + 1 >= maxbranch:
                break
        if len(paper_list) >= maxnode:
            break
    return paper_list, paper_id_list, relation_list
