import tkinter as tk
from subprocess import run
run(".\chess.exe",shell=True)
root = tk.Tk()
root.title("8x8 棋盘")
rows, cols = 8, 8
cell_size = 50  
cells = [[None for _ in range(cols)] for _ in range(rows)]
def read_chess_data(filename):
    with open(filename, 'r') as file:
        data = []
        for line in file:
            numbers = list(map(int, line.split()))
            data.append(numbers)
    return data
chess_data = read_chess_data('chess.txt')
for i in range(rows):
    for j in range(cols):
        num = chess_data[i][j] if i < len(chess_data) and j < len(chess_data[i]) else 0
        cell = tk.Label(root, text=str(num), font=("Arial", 16), width=4, height=2,
                        borderwidth=1, relief="solid")
        cell.grid(row=i, column=j, sticky="nsew")
        if (i + j) % 2 == 0:
            cell.config(bg="white")
        else:
            cell.config(bg="gray")
        cells[i][j] = cell
root.mainloop()
