/**
 * solution.cpp
 * 
 * Definitions of solution.h
 * 
 * @author kotarot
 * @version 2014-10-29
 */

#include <algorithm>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <list>
#include <sstream>
#include <vector>
#include "constants.h"
#include "solution.h"

namespace Sarumawashi {

/** Solving procedure with IDA*. Returns the sequence of moves. */
std::list<move_t> Solution::solve() {
    // We perform four phases.
    //   Phase0: G_0 = <U, D, R, L, F, B> -> G_1 = <U, D, R, L, F^2, B^2>
    //   Phase1: G_1 -> G_2 = <U, D, R^2, L^2, F^2, B^2>
    //   Phase2: G_2 -> G_3 = <U^2, D^2, R^2, L^2, F^2, B^2>
    //   Phase3: G_3 -> G_4 = {1} solved,
    for (int p = 0; p < NUM_OF_PHASES; p++) {
        clock_t start, finish;

        cphase = p;
        sequence[p].clear();
        maneuvers[p] = 0;

        start = clock();
        printf("Solution::solve(): Phase-%d has started.\n", p);
        int bound = h(root[p]);
        while (1) {
            int t = search(root[p], 0, bound, NOFACE);
            if (t == FOUND) { // Found!
                printf("Solution::solve(): Phase-%d. Found! (^o^)\n", p);
                break;
            } else if (t == NOT_FOUND) {
                std::list<move_t> e;
                printf("Solution::solve(): Phase-%d. Not found... (T_T)", p);
                printf(" final bound=%d\n", bound);
                return e;
            }
            printf("Solution::solve(): Phase-%d. Not found... (>_<)", p);
            printf(" while bound=%d\n", bound);
            bound = t;
        }
        finish = clock();
        printf("Solution::solve(): Phase-%d has finished. Time = %lf sec.\n",
            p, (double)(finish - start) / CLOCKS_PER_SEC);
        printf("%s\n", seq_to_str(sequence[p]).c_str());
    }

    return concat_seq();
}

/** Gets solution in string. */
std::string Solution::get_in_str() {
    std::stringstream ss;
    std::list<move_t> s = concat_seq();
    ss << seq_to_str(s) << "(" << moves << " moves)";
    return ss.str();
}

/** Converts sequence (list of moves) to string. */
std::string Solution::seq_to_str(std::list<move_t> seq) {
    std::stringstream ss;
    std::list<move_t>::iterator i;
    for (i = seq.begin(); i != seq.end(); i++) {
        move_t m = *i;
        if (m.f == R) {
            ss << "R";
        } else if (m.f == L) {
            ss << "L";
        } else if (m.f == U) {
            ss << "U";
        } else if (m.f == D) {
            ss << "D";
        } else if (m.f == F) {
            ss << "F";
        } else if (m.f == B) {
            ss << "B";
        } else {
            ss << "?";
        }
        if (m.r == CW) {
            ss << " ";
        } else if (m.r == HALF) {
            ss << "2 ";
        } else if (m.r == CCW) {
            ss << "' ";
        } else {
            ss << "? ";
        }
    }
    return ss.str();
}

/** Concatenates sequences of each phase into a final sequence. */
std::list<move_t> Solution::concat_seq() {
    if (!final.empty()) {
        return final;
    }
    final = sequence[0];
    for (int i = 1; i <= 3; i++) {
        if (sequence[i].empty()) {
            continue;
        }
        if (!final.empty()) {
            move_t ba = final.back();
            move_t fr = sequence[i].front();
            if (ba.f == fr.f) {
                move_t insert;
                final.pop_back();
                sequence[i].pop_front();
                insert.f = ba.f;
                int tr = ((int)fr.r + (int)ba.r) % 4;
                if (tr != 0) { // not cansel
                    insert.r = (rotation_t)tr;
                    final.push_back(insert);
                }
            }
        }
        std::list<move_t>::iterator j;
        for (j = sequence[i].begin(); j != sequence[i].end(); j++) {
            final.push_back(*j);
        }
    }
    moves = final.size();
    return final;
}

/** Heuristic function estimates cost of the path (n -> goal) */
int Solution::h(const BasicCube3 &n) {
    // We have to estimate the number of moves from n to goal, which can not 
    // exceed the real number.
    if (cphase == 0) {
        return h0(n);
    } else if (cphase == 1 || cphase == 2) {
        return h1(n);
    } else {
        return h2(n);
    }
}

int Solution::h0(const BasicCube3 &n) {
    return 0;
}

int Solution::h1(const BasicCube3 &n) {
    // Sum of manhattan distance (hamming distance) of all corners/edges.
    // Considering only positions but rotations.
    int sum = 0, c = 0, e = 0;
    for (int i = 0; i < NUM_OF_SUBCUBES; i++) {
        // corners
        if (default_pos[i][0] == 0) {
            sum += abs(n.cpos[c].z - default_pos[i][1])
                 + abs(n.cpos[c].y - default_pos[i][2])
                 + abs(n.cpos[c].x - default_pos[i][3]);
            c++;
        }
        // edges
        else {
            sum += abs(n.epos[e].z - default_pos[i][1])
                 + abs(n.epos[e].y - default_pos[i][2])
                 + abs(n.epos[e].x - default_pos[i][3]);
            e++;
        }
    }
    return sum / 2;
}

int Solution::h2(const BasicCube3 &n) {
    // Number of faces which is not arranged.
    // If all four edges or corners are not in the correct positions,
    // the face is considered to be unarranged.
    int sum, sum_corner = 0, sum_edge = 0, c = 0, e = 0;
    int incorrect_corner[NUM_OF_FACES] = {0};
    int incorrect_edge[NUM_OF_FACES] = {0};

    for (int i = 0; i < NUM_OF_SUBCUBES; i++) {
        // When the corner is in an incorerct position...
        if (default_pos[i][0] == 0) {
            if (n.cpos[c].x != default_pos[i][3] ||
                n.cpos[c].y != default_pos[i][2] ||
                n.cpos[c].z != default_pos[i][1]) {

                // R-face (corner)
                if (i == SUFR || i == SURB || i == SDBR || i == SDRF) {
                    incorrect_corner[R]++;
                }
                // L-face (corner)
                else if (i == SULF || i == SUBL || i == SDLB || i == SDFL) {
                    incorrect_corner[L]++;
                }
                // U-face (corner)
                if (i == SUFR || i == SULF || i == SUBL || i == SURB) {
                    incorrect_corner[U]++;
                }
                // D-face (corner)
                else if (i == SDRF || i == SDFL || i == SDLB || i == SDBR) {
                    incorrect_corner[D]++;
                }
                // F-face (corner)
                if (i == SUFR || i == SDRF || i == SDFL || i == SULF) {
                    incorrect_corner[F]++;
                }
                // B-face (corner)
                else if (i == SURB || i == SDBR || i == SDLB || i == SUBL) {
                    incorrect_corner[B]++;
                }

                c++;
            }
        }
        // When the edge is in an incorerct position...
        else {
            if (n.epos[e].x != default_pos[i][3] ||
                n.epos[e].y != default_pos[i][2] ||
                n.epos[e].z != default_pos[i][1]) {

                // R-face (edge)
                if (i == SUR || i == SBR || i == SDR || i == SFR) {
                    incorrect_edge[R]++;
                }
                // L-face (edge)
                else if (i == SUL || i == SBL || i == SDL || i == SFL) {
                    incorrect_edge[L]++;
                }
                // U-face (edge)
                if (i == SUR || i == SUF || i == SUL || i == SUB) {
                    incorrect_edge[U]++;
                }
                // D-face (edge)
                else if (i == SDR || i == SDF || i == SDL || i == SDB) {
                    incorrect_edge[D]++;
                }
                // F-face (edge)
                if (i == SUF || i == SFR || i == SDF || i == SFL) {
                    incorrect_edge[F]++;
                }
                // B-face (edge)
                else if (i == SUB || i == SBR || i == SDB || i == SBL) {
                    incorrect_edge[B]++;
                }
            }
        }
    }
    for (int i = 0; i < NUM_OF_FACES; i++) {
        if (incorrect_corner[i] >= 4) {
            sum_corner++;
        }
        if (incorrect_edge[i] >= 4) {
            sum_edge++;
        }
    }
    sum = (sum_corner < sum_edge) ? sum_edge : sum_corner;
    if (sum < 1) {
        return 1;
    } else if (4 < sum) {
        return 4;
    }
    return sum;
}

/** Path (edge) cost function. */
inline int Solution::cost(const BasicCube3 &n, const BasicCube3 &succ) {
    // Always returns one.
    return 1;
}

/** Node expanding function. Returns all faces and all rotations. */
std::vector<BasicCube3> Solution::successors(const BasicCube3 &n) {
    std::vector<BasicCube3> ret;
    for (int f = 0; f < NUM_OF_FACES; f++) {
        for (int r = 1; r <= 3; r++) {
            BasicCube3 c = n;
            c.basic_turn((face_t)f, (rotation_t)r);
            ret.push_back(c);
        }
    }
    return ret;
}

/** Search function called recursively.
    @param node n, cost from root to n, bound, prev rotation face. */
int
Solution::search(BasicCube3 &n, const int g, const int bound, const face_t pf) {
    maneuvers[cphase]++;
    int f = g + h(n);
    // Exceeds depth bound.
    if (f > bound) {
        return f;
    }

    bool found = is_finished(n);
    if (found) {
        if (cphase != 3) {
            root[cphase + 1] = n;
        }
        printf("Solution::search(): Now, found! depth=%d maneuvers=%d\n",
            g, maneuvers[cphase]);
        return FOUND;
    }

    int min = INT_MAX;
    std::vector<BasicCube3> succs = successors(n);
    // 6 faces x 3 rotations = 18 patterns
    // I don't use iteration here because the value will be used later.
    for (int p = 0; p < 18; p++) {
        // Face and rotation.
        face_t f = (face_t)(p / 3);
        rotation_t r = (rotation_t)((p % 3) + 1);

        // These two (A) and (B) pruning search nodes.
        // (A) The same face can't be continued.
        if (f == pf) {
            continue;
        }
        // (B) Continuing opposite faces is not permitted,
        //     and sequence L->R etc. is prunable because it is same as R->L.
        /*if ((f == R && pf == L && ppf == R) || (f == L && pf == R && ppf == L)
         || (f == U && pf == D && ppf == U) || (f == D && pf == U && ppf == D)
         || (f == F && pf == B && ppf == F) || (f == B && pf == F && ppf == B)){
        */
        if ((f == R && pf == L) || (f == U && pf == D) || (f == F && pf == B)) {
            continue;
        }

        // In phase-1, 2, 3 -> Only half turns on F, B.
        if (cphase == 1 || cphase == 2 || cphase == 3) {
            if ((f == F && (r == CW || r == CCW)) ||
                (f == B && (r == CW || r == CCW))) {
                continue;
            }
        }
        // In phase-2, 3 -> Only half turns on R, L.
        if (cphase == 2 || cphase == 3) {
            if ((f == R && (r == CW || r == CCW)) ||
                (f == L && (r == CW || r == CCW))) {
                continue;
            }
        }
        // In phase-3 -> Only half turns on U, D.
        if (cphase == 3) {
            if ((f == U && (r == CW || r == CCW)) ||
                (f == D && (r == CW || r == CCW))) {
                continue;
            }
        }

        BasicCube3 s = succs[p];
        int t = search(s, g + cost(n, s), bound, f);
        if (t == FOUND) {
            move_t m = {f, r};
            sequence[cphase].push_front(m);
            return FOUND;
        } else if (t < min) {
            min = t;
        }
    }
    return min;
}

bool Solution::is_finished(BasicCube3 &n) {
    if (cphase == 0) {
        return finished_phase0(n);
    } else if (cphase == 1) {
        return finished_phase1(n);
    } else if (cphase == 2) {
        return finished_phase2(n);
        //return n.is_solved();
    } else if (cphase == 3) {
        return n.is_solved();
    }
    return false;
}

/** Test finished phase-0. */
bool Solution::finished_phase0(const BasicCube3 &n) {
    int e = 0;
    for (int i = 0; i < NUM_OF_SUBCUBES; i++) {
        // edges
        if (default_pos[i][0] == 1) {
            if (n.epos[e].r % 2 != 0) {
                return false;
            }
            e++;
        }
    }
    return true;
}

/** Test finished phase-1. */
bool Solution::finished_phase1(const BasicCube3 &n) {
    int c = 0, e = 0;
    for (int i = 0; i < NUM_OF_SUBCUBES; i++) {
        // corners
        if (default_pos[i][0] == 0) {
            if (n.cpos[c].r % 3 != 0) {
                return false;
            }
            c++;
        // edges
        } else {
            // Flips: No need to check this, because this must be true.
            //if (n.epos[e].r % 2 != 0) {
            //    return false;
            //}
            // 3.FR / 4.FL / 15.BR / 16.BL are in E-slice.
            if (i == SFR || i == SFL || i == SBR || i == SBL) {
                if (n.epos[e].y != 0) {
                    return false;
                }
            }
            e++;
        }
    }
    return true;
}

/** Test finished phase-2. */
bool Solution::finished_phase2(BasicCube3 &n) {
    // [TODO] This function should be splited to some functions.
BEGIN_SCOPE
    int c = 0, e = 0;
    for (int i = 0; i < NUM_OF_SUBCUBES; i++) {
        // corners
        if (default_pos[i][0] == 0) {
            // Pivots: No need to check this, because this must be true.
            //if (n.cpos[c].r % 3 != 0) {
            //    return false;
            //}
            // Check positions.
            // [Truth table]
            // same_x same_y same_z | output
            //   0      0      0    |   1
            //   0      0      1    |   0
            //   0      1      0    |   0
            //   0      1      1    |   1
            //   1      0      0    |   0
            //   1      0      1    |   1
            //   1      1      0    |   1
            //   1      1      1    |   0
            bool same_x = (n.cpos[c].x == default_pos[i][3]);
            bool same_y = (n.cpos[c].y == default_pos[i][2]);
            bool same_z = (n.cpos[c].z == default_pos[i][1]);
            if ((same_x == false && same_y == false && same_z == false) ||
                (same_x == false && same_y == true  && same_z == true ) ||
                (same_x == true  && same_y == false && same_z == true ) ||
                (same_x == true  && same_y == true  && same_z == false)) {
                return false;
            }
            c++;
        }
        // edges
        else {
            // Flips: No need to check this, because this must be true.
            //if (n.epos[e].r % 2 != 0) {
            //    return false;
            //}
            // Check positions.
            // 3.FR / 4.FL / 15.BR / 16.BL are in E-slice.
            // No need to check this.
            //if (i == SFR || i == SFL || i == SBR || i == SBL) {
            //    if (n.epos[e].y != 0) {
            //        return false;
            //    }
            //}
            // 8.UR / 9.UL / 10.DR / 11.DL are in S-slice.
            if (i == SUR || i == SUL || i == SDR || i == SDL) {
                if (n.epos[e].z != 0) {
                    return false;
                }
            }
            e++;
        }
    }
END_SCOPE

BEGIN_SCOPE
    // No parities which means that we can arrange corners with 3-cycle.
    // [TODO] This kind of operations must be described in BasicCube3.
    std::vector<corner_t> ccycle;
    for (int nz = -1; nz <= 1; nz += 2) {
        for (int ny = -1; ny <= 1; ny += 2) {
            for (int nx = -1; nx <= 1; nx += 2) {
                ccycle.push_back(n.corner(nx, ny, nz));
            }
        }
    }
    // Counts how many loops and how many elements in a loop.
    std::vector<corner_t> open;
    std::vector<int> loops;
    for (int i = 0; i < 8; i++) {
        corner_t start = ccycle[i];
        if (find(open.begin(), open.end(), start) == open.end()) {
            int count = 0;
            corner_t current = start;
            corner_t next;
            do {
                open.push_back(current);
                count++;
                next = ccycle[current];
                current = next;
            } while (start != next);
            loops.push_back(count);
        }
    }
    int sum = 0;
    for (std::vector<int>::iterator i = loops.begin(); i != loops.end(); i++) {
        sum += *i + 1;
    }
    if (sum % 2 == 1) {
        return false;
    }
END_SCOPE

BEGIN_SCOPE
    // NG, if the three cubes with the same color on U-face, in the current
    // position and the positions after R^2, L^2, F^2, B^2
    std::vector<BasicCube3> targets;
    targets.push_back(n);
    for (int f = 0; f < 6; f++) {
        if (f == (int)U || f == (int)D) {
            continue;
        }
        BasicCube3 c = n;
        c.basic_turn((face_t)f, HALF);
        targets.push_back(c);
    }
    for (int i = 0; i < 5; i++) {
        BasicCube3 t = targets[i];
        int c = 0, count_u = 0;
        for (int i = 0; i < NUM_OF_SUBCUBES; i++) {
            // corners
            if (default_pos[i][0] == 0) {
                if (i == SUFR || i == SULF || i == SUBL || i == SURB) {
                    if (t.cpos[c].y == -1) {
                        count_u++;
                    }
                }
                c++;
            }
        }
        if (count_u == 1 || count_u == 3) {
            return false;
        }
    }
END_SCOPE

    return true;
}

} // end of namespace
