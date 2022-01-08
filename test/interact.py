import sys
import json
import dash
from dash import dcc
from dash import html
import dash_cytoscape as cyto
import dash_bootstrap_components as dbc
from dash.dependencies import Input, Output
import networkx as nx
import paperpy
import nodepy as ndp

# Preprocessing -- get data from argv
script, rel_file, pos_file, info_file = sys.argv

with open(rel_file, 'r') as f1, open(pos_file, 'r') as f2, open(info_file, 'r') as f3:
    relation = [tuple(map(int, i.split(' '))) for i in f1]
    position = [tuple(map(float, i.split(' '))) for i in f2]
    info = json.load(f3)

# create website

app = dash.Dash(__name__, external_stylesheets=[dbc.themes.BOOTSTRAP])
app.title = "Related Work Graph"

nodes = [
    {
        'data': {'id': id_, 'info': info[id_]},
        'position': {'x': x, 'y': y}
    }
    for id_, (x, y) in enumerate(position)
]

edges = [
    {'data': {'source': source, 'target': target}}
    for source, target in relation
]

elements = nodes + edges

default_stylesheet = [
    {
        'selector': 'node',
        'style': {
            'background-color': '#0a4670',
            'width': "200%",
            'height': "200%",
            'label': 'data(id)'
        }
    },
    {
        'selector': 'edge',
        'style': {
            'line-color': '#9fb9cc',
            'width': "30%",
            'height': "30%"
        }
    }
]

navbar = dbc.NavbarSimple(
    children=[
        dbc.NavItem(
            dbc.NavLink(
                "Source Code",
                href="https://github.com/yichi170/RelatedWorkGraph",
            )
        ),
    ],
    brand="Numerical Software Development Final Project — Related Work Graph",
    brand_href="#",
    color="#17be", # 1ac, 13a6
    dark=True,
)

body_layout = dbc.Container(
    [
        dbc.Row([
            dbc.Col(
                [
                    dbc.Row([
                        cyto.Cytoscape(
                            id='cytoscape-event',
                            elements=elements,
                            stylesheet=default_stylesheet,
                            style={'width': '100%', 'height': '600px'},
                            layout={
                                'name': 'preset'
                            }
                        )
                    ]), 
                ], 

            ), 
            dbc.Col(
                [
                    dcc.Markdown(
                        """
                        #### Information about this paper:
                        """
                    ),
                    dbc.Alert(
                        id="node-info",
                        children="Click on a node to see the information.",
                        color="secondary",
                        style={"overflow": "scroll"}
                    )
                ],
            )
        ]),
        # footer
        dbc.Row(
            [
                dcc.Markdown(
                    """
                    Data from
                    Semantic Scholar
                    """
                )
            ],
            style={"fontSize": 12, "color": "gray"},
        ),
    ], style={"marginTop": 10}
)
app.layout = html.Div([navbar, body_layout])

@app.callback(
    Output("node-info", "children"),
    [Input("cytoscape-event", "selectedNodeData")]
)
def display_nodedata(datalist):
    contents = "Click on a node to see the information."
    if datalist is not None:
        if len(datalist) > 0:
            data = datalist[-1]
            contents = []

            contents.append(
                html.Div([
                    html.H5(
                        [
                            data["info"]["title"],
                            " ",
                            html.A(
                                "[Link]",
                                href=data["info"]["url"]
                            )
                        ]
                    )
                ])
            )
            
            contents.append(
                html.P(
                    "authors: "
                    + str(", ".join(i["name"] for i in data["info"]["authors"]))
                )
            )
            
            contents.append(
                html.P(
                    "Published year: "
                    + str(data["info"]["year"])
                )
            )
            
            contents.append(
                html.P(
                    "citation count: "
                    + str(data["info"]["citationCount"])
                )
            )

            contents.append(
                dcc.Markdown(
                    "Abstract: "
                    + str(data["info"]["abstract"])
                )
            )
    return contents

@app.callback(
    Output("node-info", "style"),
    [Input("cytoscape-event", "selectedNodeData")]
)
def change_info_style(datalist):
    if datalist is not None:
        if len(datalist) > 0:
            return {"height": "80%", "overflow": "scroll"}
    return {"overflow": "hidden"}

if __name__ == '__main__':
    app.run_server(debug=True)
