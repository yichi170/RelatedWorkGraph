import nodepy as ndp

def test():
    relation = [[0, 1], [0, 2], [1, 2]]
    system = ndp.NodeSystem(3, 1000, 1000, 100.0, 100, relation)
    system.run()
    pos = system.getPos()
    print(pos)

if __name__ == '__main__':
    test()
