#include <bits/stdc++.h>
#include <iostream>
#include <fstream>

using namespace std;

/* Structure that stores coordinates of a point in matrix. */
struct Point {
    int x;
    int y;
};

/* 	Structure that is used for being stored in a queue, it contains the
coordinates of a point and the distance from the start to the point where we are. */ 
struct queueNode {
    Point point;
    int distance;
};
/* We know that we are on the edge of the grid so we must check if Gigel can 
get out of the grid based on the bridge he is currently standing on. */
bool check_on_edge(char** mat, int x, int y,
	int nr_of_rows, int nr_of_columns) {
    /* We know that the current position is a bridge that allows us to go
    either up or down so the way to get out of the grid is to be either at the
    first row of the matrix or at the last row. */
    if (mat[x][y] == 'V') {
		return ( x == 0 || x == nr_of_rows - 1);
	/* We know that the current position is a bridge that allows us to go
	either left or right so the way to get out of the grid is to be either at
	the first column of the matrix or at the last column. */
	} else if (mat[x][y] == 'O') {
		return (y == 0 || y == nr_of_columns - 1 );
	/* We know that the current position is a bridge that allows us to go in
	each direcetion so the only condition is to be on the edge of the grid. */
	} else if (mat[x][y] == 'D') {
	 	return (x == 0 || x == nr_of_rows - 1 || y == 0
	 		|| y == nr_of_columns - 1);
	}
}

int find_minimum_moves(char** matrix, int nr_of_rows,
	int nr_of_columns, int x_start, int y_start) {
	/* Arrays that are uset to get row and column of the 4 neighbours of a
	cell insted doing it (x+1,y),(x-1,y),(x,y+1),(x,y-1). */
    int dx[] = { 1, -1, 0, 0 };
    int dy[] = { 0, 0, 1, -1 };
    /* Queue used for BFS, in which we will store visited nodes. */
    queue<queueNode> traversal_queue;
    /* If we are exactely on the edge and we can escape the greed we can end
    the program. */
    if (check_on_edge(matrix, x_start, y_start, nr_of_rows, nr_of_columns))
        return 1;
    /* We insert our stating position in the queue. */
    Point source = {x_start, y_start};
    queueNode s = {source, 0};
    traversal_queue.push(s);
	/* We create a matrix in which we withhold if a position is visited or not.
    */
    bool visited[nr_of_rows][nr_of_columns];
	memset(visited, false, sizeof visited);
	/* Here we start BFS from source cell. */
    while (traversal_queue.size() > 0) {
        queueNode position = traversal_queue.front();
        Point point = position.point;
        /* If we have reached the edge of the grid an we can exit we have an
        awnser. */
        if (check_on_edge(matrix, point.x,
        	point.y, nr_of_rows, nr_of_columns)) {
            return position.distance + 1;
        }
        /* Otherwise dequeue the front cell in the queue and enqueue its
        adjacent cells. */
        traversal_queue.pop();
        /* We are at the point were we must find which of the neighbours of
        the current cell are allowed in the queue based on the bridge model. */
		int aux_start, aux_end;
		if (matrix[point.x][point.y] == 'V') {
			aux_start = 0;
			aux_end = 2;
		} else if (matrix[point.x][point.y] == 'O') {
			aux_start = 2;
			aux_end = 4;
		} else {
			aux_start = 0;
			aux_end = 4;
		}
		/* So based on the mode of the bridge we know the fact taht the first
		two elements are for vertical usage, the other two for horizontal usage,
		and in case we habe a double bridge all the cells can be stored */
        for (int j = aux_start; j < aux_end; j++) {
            int x = point.x + dx[j];
            int y = point.y + dy[j];
            /* If adjacent cell is not water and it is not visited yet,
            enqueue it. */
            if (matrix[x][y] != '.' && !visited[x][y]) {
                visited[x][y] = true;
                /* Mark cell as visited and enqueue it. */
				queueNode adiacent_cell = { {x, y},
                                      position.distance + 1 };
                traversal_queue.push(adiacent_cell);
            }
        }
    }
    /* Return -1 if destination cannot be reached. */
    return -1;
}

int main() {
	int nr_of_rows, nr_of_columns;
	int x_start, y_start;
	ifstream input_file("poduri.in");
	ofstream output_file("poduri.out");

	input_file >> nr_of_rows >> nr_of_columns;
	input_file >> x_start >> y_start;
	x_start = x_start - 1;
	y_start = y_start - 1;

	char **matrix = new char *[nr_of_rows];
	for (int i = 0; i < nr_of_rows; ++i) {
		matrix[i] = new char[nr_of_columns];
	}

	for (int i = 0; i < nr_of_rows; ++i) {
		for (int j = 0; j < nr_of_columns; ++j) {
			input_file >> matrix[i][j];
		}
	}

	output_file << find_minimum_moves(matrix, nr_of_rows,
		nr_of_columns, x_start, y_start);
    input_file.close();
    output_file.close();
    return 0;
}
