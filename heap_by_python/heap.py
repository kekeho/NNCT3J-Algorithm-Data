class Heap():
    def __init__(self):
        self.box = []
        self.size = 0

    def insert(self, x):
        self.box.append(x)
        self.size += 1

        now = self.size - 1
        while True:
            mother = int((now - 1) / 2)
            if now == 0:
                break
            elif self.box[mother] < self.box[now]:
                self.box[mother], self.box[now] = self.box[now], self.box[mother]
                now = mother
            else:
                break

    def top(self):
        return self.box[0]

    def printAll(self):
        for inbox in self.box:
            print(inbox)

    def delete(self):
        now = self.size - 1
        self.box[0] = self.box[now]
        now = 0

        while True:
            leftson = self.box[int(now * 2 + 1)]
            rightson = self.box[int(now * 2 + 1)]
            bigson = 0
            bigsonSize = 0

            # compare both of son
            if leftson < rightson:
                bigson = rightson
                bigsonSize = now * 2 + 2
            else:
                bigson = leftson
                bigsonSize = now * 2 + 1

            # swap
            if bigson > self.box[now]:
                bigson, self.box[now] = self.box[now], bigson
                now = bigsonSize
            else:
                break
            self.size -= 1
        self.box.pop(0)


#test
heap = Heap()
heap.insert(1)
heap.insert(31)
heap.insert(42)
heap.insert(5)
heap.insert(91)
heap.printAll()
print('---')
heap.delete()
heap.delete()
heap.delete()
heap.printAll()
