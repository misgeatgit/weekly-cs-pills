/* Solver.cc *
 * Copyright (C) <2014> <misgana.bayetta@gmail.com>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */
#include "Solver.h"
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;
#define DEBUG 0
/*
 struct cell{
 int i;
 int j;
 int value;
 };
 struct cell_candidate{
 int i;
 int j;
 vector <int> candidates;
 };
 */
vector<vector<vector<int> > > Solver::build_candidates() {
	vector<vector<vector<int> > > candidates(9,
			vector<vector<int> >(9, vector<int>(0, 0)));
	map<int, vector<int>> grid_candidate_map { { 1, grid_candidate(0, 0) }, { 2,grid_candidate(0, 3) },
		                                       { 3, grid_candidate(0, 6) }, { 4,grid_candidate(3, 0) },
		                                       { 5, grid_candidate(3, 3) }, { 6,grid_candidate(3, 6) },
		                                       { 7, grid_candidate(6, 0) }, { 8,grid_candidate(6, 3) },
		                                       { 9, grid_candidate(6, 6) } };
	for (int j = 0; j < 9; j++) {
		for (int i = 0; i < 9; i++) {
			//what possible values can be set for the cell by row wise rule
			vector<int> row_candidates = row_candidate(i);

			if (_board[i][j] == 0) {
				vector<int> col_candidates;
				vector<int> grid_candidates;
				vector<vector<int> > all_candidates;
				//grid candidate lookup here,identify in which grid is the cell and get possible
				//values for the cell in that particular grid by grid wise rule
				int rdiff = 9 - (i + 1);
				int cdiff = 9 - (j + 1);
				if (rdiff <= 8 && rdiff >= 6) {
					if (cdiff <= 8 && cdiff >= 6) {
						grid_candidates = grid_candidate_map[1];
					}
					if (cdiff <= 5 && cdiff >= 3) {
						grid_candidates = grid_candidate_map[2];
					}
					if (cdiff <= 2 && cdiff >= 0) {
						grid_candidates = grid_candidate_map[3];
					}
				}
				if (rdiff <= 5 && rdiff >= 3) {
					if (cdiff <= 8 && cdiff >= 6) {
						grid_candidates = grid_candidate_map[4];
					}
					if (cdiff <= 5 && cdiff >= 3) {
						grid_candidates = grid_candidate_map[5];
					}
					if (cdiff <= 2 && cdiff >= 0) {
						grid_candidates = grid_candidate_map[6];
					}
				}
				if (rdiff <= 2 && rdiff >= 0) {
					if (cdiff <= 8 && cdiff >= 6) {
						grid_candidates = grid_candidate_map[7];
					}
					if (cdiff <= 5 && cdiff >= 3) {
						grid_candidates = grid_candidate_map[8];
					}
					if (cdiff <= 2 && cdiff >= 0) {
						grid_candidates = grid_candidate_map[9];
					}
				}

				//what possible values can be set for the cell by column wise  rule
				col_candidates = column_candidate(j);

				all_candidates.push_back(grid_candidates);
				all_candidates.push_back(row_candidates);
				all_candidates.push_back(col_candidates);
				//get the intersection of the grid wise, row wise and col wise values.
				//which will be the final possible value the particular cell @ [i,j]
				candidates[i][j] = intersect(all_candidates);

			} else {
				candidates[i][j] = vector<int> { _board[i][j] };
			}
		}
	}
	return candidates;
}

vector<int> Solver::grid_candidate(int rstart, int cstart) {
	vector<int> existing;
	for (int i = rstart; i <= rstart + 2; i++) {
		for (int j = cstart; j <= cstart + 2; j++) {
			if (_board[i][j] != 0) {
				existing.push_back(_board[i][j]);
			}
		}
	}
	return disjoint(existing);
}

vector<int> Solver::row_candidate(int rindex) {
	vector<int> existing;
	for (int j = 0; j < 9; j++) {
		if (_board[rindex][j] != 0) {
			existing.push_back(_board[rindex][j]);
		}
	}
	return disjoint(existing);
}
vector<int> Solver::column_candidate(int colindex) {
	vector<int> existing;
	for (auto i = 0; i < 9; i++) {
		if (_board[i][colindex] != 0) {
			existing.push_back(_board[i][colindex]);
		}
	}
	return disjoint(existing);
}
vector<int> Solver::intersect(vector<vector<int> > cell_candidates) {
	vector<int> intersect;
	for (auto it = cell_candidates.begin(); it != cell_candidates.end(); ++it) {
		vector<int> temp;
		if (distance(cell_candidates.begin(), it) == 0) {
			intersect = *it;
		} else {
			sort(intersect.begin(), intersect.end());
			sort((*it).begin(), (*it).end());
			set_intersection(intersect.begin(), intersect.end(), (*it).begin(),
					(*it).end(), back_inserter(temp));
			intersect = temp;
		}
	}
	return intersect;
}

vector<int> Solver::disjoint(vector<int> val_existing) {
	vector<int> disjoint_set;
	for (auto i = 0; i < 9; i++) {
		bool exist = false;
		for (auto it = val_existing.begin(); it != val_existing.end(); ++it) {
			if (CELL_VALUES[i] == *it) {
				exist = true;
				break;
			}
		}
		if (!exist) {
			disjoint_set.push_back(CELL_VALUES[i]);
		}
	}
	return disjoint_set;
}
int* Solver::solve() {
	vector<vector<vector<int> > > soln_matrix;
	int singles_count = 0;
	int iter = 0;
	while (singles_count != 81) {
		singles_count = 0;
		cout << "RUNNING..." << iter << endl;
		soln_matrix = build_candidates();
		iter++;
		for (auto row_col_candidates = soln_matrix.begin();
				row_col_candidates != soln_matrix.end(); ++row_col_candidates) {
			for (auto col_candidates = (*row_col_candidates).begin();
					col_candidates != (*row_col_candidates).end();
					++col_candidates) {
				if ((*col_candidates).size() == 1) {
					singles_count += 1;
					int row = distance(soln_matrix.begin(), row_col_candidates);
					int col = distance((*row_col_candidates).begin(),
							col_candidates);

					_board[row][col] = (*col_candidates)[0];
				}
			}
		}
	}
	int * result = (int *) malloc(sizeof(int) * 81);
	memcpy(result, _board, sizeof(int) * 81);
	printd(_board, soln_matrix);
	return result;
}
//for debugging
void Solver::printd(int board[9][9],
		vector<vector<vector<int> > > soln_matrix) {
	cout << "INPUT" << endl;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			cout << board[i][j] << " ";
		}
		cout << endl;
	}
#if 0
	cout << "CURRENT ITERATION POSSIBLE VALUES" << endl;
	for (auto i = soln_matrix.begin(); i != soln_matrix.end(); ++i) {
		for (auto j = (*i).begin(); j != (*i).end(); ++j) {
			int row = distance(soln_matrix.begin(), i);
			int col = distance((*i).begin(), j);
			cout << "@ [" << row << "][" << col << "] {";
			for (auto k = (*j).begin(); k != (*j).end(); ++k) {
				cout << *k << ",";
			}
			cout << "}" << endl;
		}
	}
#endif
}
int main() {
	int board[9][9] = { { 0, 0, 4, 0, 5, 3, 0, 0, 6 },
			            { 0, 0, 1, 4, 0, 2, 0, 0, 0 },
			            { 3, 0, 6, 8, 0, 0, 0, 0, 0 },
			            { 0, 9, 3, 0, 0, 0, 8, 0, 0 },
			            { 0, 2, 5, 3, 0, 1, 6, 7, 0 },
			            { 0, 0, 8, 0, 0, 0, 4, 2, 0 },
			            { 0, 0,	0, 0, 0, 5, 3, 0, 7 },
			            { 0, 0, 0, 7, 0, 9, 1, 0, 0 },
			            { 5, 0, 0, 1, 4, 0, 9, 0, 0 } };
	Solver s(board);
	s.solve();
//test
#if DEBUG
	vector<int> x {1, 2, 8, 3, 4, 5};
	vector<int> y {4, 5, 6, 8};
	vector<int> z {4, 6, 7, 8};
	vector<vector<int>> collection {x, y, z};
	vector<int> xyz_intersection = s.intersect(collection);
	vector<int> x_disjoint = s.disjoint(y);
	vector<int> col_cand = s.column_candidate(6);
	vector<int> row_cand = s.row_candidate(0);
	vector<int> grid_cand = s.grid_candidate(0, 6);
	vector<int> cell_cand = s.intersect(vector<vector<int> > {grid_cand,
				col_cand, row_cand});
	cout << endl << "COL CANDIDATE :";
	for (int x : col_cand)
	cout << x << ",";
	cout << endl << "ROW CANDIDATE  :";
	for (int x : row_cand)
	cout << x << ",";
	cout << endl << "GRID CANDIDATE :";
	for (int x : grid_cand)
	cout << x << ",";
	cout << endl << "CELL CANDIDATE :";
	for (int x : cell_cand)
	cout << x << ",";
#endif
//
	return 0;
}
