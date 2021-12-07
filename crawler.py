from bs4 import BeautifulSoup
import requests

root = "https://api.semanticscholar.org/graph/v1"
maxnode = 1000

paper_list = []
id_to_index = dict()
index_to_id = dict()
relation_list = []

def get_paper_url(arxiv_id):
	return f"arxiv.org/pdf/{arxiv_id}"

def main():
	# get Input from console
	mode = input("Input the mode (citations/references): ")
	maxbr = input("Input the maximum number of branch: ")
	if mode != "citations":
		mode = "references"
	title = input("Input the title of the paper: ").replace(' ', '+')
	
	# Search for this paper
	r = requests.get(root+f"/paper/search?query={title}") # paperID, title
	data = r.json()
	# put the candidate paper into the list [{paper1}, {paper2}]
	# {"paperId": "", "title": ""}
	
	paper_list.extend(data['data'])

	for i, paper in enumerate(data['data']):
		id_to_index[paper['title']] = i
		index_to_id[i] = paper['title']

	for i, result in enumerate(paper_list):
		fln = requests.get(root + f"/paper/{result['paperId']}?fields={mode}").json() # the node in the first layer

		length = len(paper_list)
		for j, paper in enumerate(fln[mode]):
			id_to_index[paper['title']] = length + j
			index_to_id[length + j] = paper['title']
			relation_list.append([i, j])
		paper_list.extend(fln[mode])
		if len(paper_list) > maxnode:
			break
	
	print(paper_list)

if __name__ == '__main__':
	main()