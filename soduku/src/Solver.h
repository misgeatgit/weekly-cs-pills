/* Solver.h
 * Copyright (C) <2014> <misgana.bayetta@gmail.com>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */
#ifndef _SOLVER_H_
#define _SOLVER_H_
#include <iostream>
#include <vector>

using namespace std;

class Solver {
protected:
	int _board[9][9];
	const int CELL_VALUES[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int ij = 0;
public:
	Solver(int board[9][9]) {
		copy(&board[0][0],&board[0][0]+81,&_board[0][0]);
	}
//private:
	/*
	 * Builds all possible value that an empty cell (0) could take by looking
	 * all possible grid membership of the cell and what values in each grid
	 * it can take,all possible values it can take row wise and all possible
	 * values it can column wise. Finally the minumum set is returned as the
	 * set of all possible values that the empty cell can take.
	 * @param int * board
	 * @return set of possible values that the empty cell can be replaced with
	 */
	vector<vector<vector<int> > > build_candidates();
	/**
	 * @return all missing values in a 3X3 grid
	 */
	vector<int> grid_candidate(int rstart, int cstart);
	/*
	 * @return all missing values of row rindex
	 */
	vector<int> row_candidate(int rindex);
	/*
	 * @return all missing values of column colindex
	 */
	vector<int> column_candidate(int colindex);
	/*
	 * @return a vector with minimum size from a set of vectors
	 */
	vector<int> intersect(vector<vector<int> > cell_candidates);
	/*
	 * return the disjoint set between BOARD_NUMBERS and val_existing
	 */
	vector<int> disjoint(vector<int> val_existing);
	/*
	 * starting point
	 */
	int* solve();
	void printd(int board[9][9], vector<vector<vector<int> > > soln_matrix);
};

#endif /* _SOLVER_H_ */
