class MinNode:
    def __init__(self, value = None):
        self.value = value if value else float("inf") 
        self.child = []
    
    def search(self, alpha, beta):
        for nextState in self.child:
            self.value = min(self.value, nextState.search(alpha, beta))
            beta = min(beta, self.value)
            if alpha >= beta:
                return self.value
        return self.value
    
class MaxNode:
    def __init__(self, value = None):
        self.value = value if value else float("-inf") 
        self.child = []
        
    def search(self, alpha, beta):
        for nextState in self.child:
            self.value = max(self.value, nextState.search(alpha, beta))
            alpha = max(alpha, self.value)
            if alpha >= beta:
                return self.value
        return self.value

def simulation(a = MaxNode):
    b = MinNode if a is MaxNode else MaxNode
    nodes = [5, 6, 7, 4, 5, 3, 6, 6, 9, 7, 5, 9, 8, 6]
    relation_logic = [[2, 3, 1, 1, 2, 1, 1, 2, 1], [2, 1, 2, 1, 1, 2], [2, 2, 2], [3]]
    nodes = [a(i) for i in nodes]
    for i in range(len(relation_logic)):
        node_class = b if i%2==0 else a
        for j in relation_logic[i]:
            node = node_class()
            node.child = nodes[:j]
            del nodes[:j]
            nodes.append(node)
    root = nodes[0]
    root.value = float("-inf") if a is MaxNode else float("inf")
    return nodes[0]

def display(node):
    level = [node]
    cur_cnt = 1
    next_cnt = 0
    while level:
        cur = level.pop(0)
        print(cur.value, end=" ")
        cur_cnt -= 1    
        for i in cur.child:
            level.append(i)
            next_cnt += 1
        if cur_cnt == 0:
            cur_cnt = next_cnt
            next_cnt = 0
            print()

root = simulation(MaxNode)
root.search(float("-inf"),float("inf"))
print(root.value)
display(root)
