def numCells(grid):
    count = 0
    for n in range(len(grid)):
        for m in range(len(grid[0])):
            dominant = True
            for row in range(n - 1, n + 2):
                for col in range(m - 1, m + 2):
                    if col == m and row == n:

                        print(row, col)
                    else: 
                         print("s")
                            
            if dominant == True:
                count += 1
    print(count)

s = [[1,4,3],[2,2,4],[2,2,5],[1,2,5]]

numCells(s)