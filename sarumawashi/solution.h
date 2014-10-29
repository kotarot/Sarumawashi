/**
 * solution.h
 * 
 * Solution class of a cube puzzle, using BasicCube3 which is lighter in memory
 * compared to the complete cube class. The algorithm is based on
 * Thistlethwaite's algorithm and uses IDA* search algorithm. This program is
 * a little bit different from the original one because it uses look-up tables.
 * 
 * @author kotarot
 * @version 2014-10-29
 */

#ifndef __SOLUTION_H__
#define __SOLUTION_H__

#define BEGIN_SCOPE {
#define END_SCOPE   }

#include <climits>
#include <list>
#include <string>
#include <vector>
#include "basiccube3.h"

namespace Sarumawashi {

/** For searching. */
const int FOUND = -1;
const int NOT_FOUND = INT_MAX;

class Solution {
public:
    Solution() {};
    Solution(BasicCube3 r) { root[0] = r; };
    ~Solution() {};

    /** Number of phases. */
    static const int NUM_OF_PHASES = 4;

    /** Sets the root node. */
    void set_root(BasicCube3 r) { root[0] = r; }
    /** Solving procedure with IDA*. Returns the sequence of moves. */
    std::list<move_t> solve();
    /** Gets solution in string. */
    std::string get_in_str();

    /** Converts sequence (list of moves) to string. */
    static std::string seq_to_str(std::list<move_t> seq);

private:
    /** Root node of each phase. */
    BasicCube3 root[NUM_OF_PHASES];

    /** Current executing phase. */
    int cphase;
    /** The sequence of solution. Final result and results in each phase. */
    std::list<move_t> sequence[NUM_OF_PHASES];
    /** Numbers of maneuvers for each phase. */
    int maneuvers[NUM_OF_PHASES];
    /** Final solution. */
    std::list<move_t> final;
    /** Total moves. */
    int moves;

    /** Concatenates sequences of each phase into a final sequence. */
    std::list<move_t> concat_seq();

    /** Heuristic function estimates cost of the path (n -> goal) */
    int h(const BasicCube3 &n);
    int h0(const BasicCube3 &n);
    int h1(const BasicCube3 &n);
    int h2(const BasicCube3 &n);
    /** Path (edge) cost function. */
    inline int cost(const BasicCube3 &n, const BasicCube3 &succ);
    /** Node expanding function. Returns all faces and all rotations. */
    std::vector<BasicCube3> successors(const BasicCube3 &n);

    /** Search function called recursively.
        @param node n, cost from root to n, bound, prev rotation face. */
    int search(BasicCube3 &n, const int g, const int bound, const face_t pf);

    /** Test finished */
    bool is_finished(BasicCube3 &n);
    /** Test finished phase-0.
        There are no flips in all edges.
        Finished states are in Group <U, D, R, L, F^2, B^2> */
    bool finished_phase0(const BasicCube3 &n);
    /** Test finished phase-1.
        There are no flips or pivots in all edges/corners,
        and FR/FL/BR/BL are in E slice.
        Finished states are in Group <U, D, R^2, L^2, F^2, B^2> */
    bool finished_phase1(const BasicCube3 &n);
    /** Test finished phase-2.
        There are no flips or pivots in all edges/corners,
        and FR/FL/BR/BL are in E slice,
        and UF/UB/DF/DB are in M slice,
        and UR/UL/DR/DL are in S slice (This must be true
            iff two above are satisfied.),
        and corner-cube must not be the position whose just two coordinates
            are same as the defalut position (in the orbit),
        Finished states are in Group <U^2, D^2, R^2, L^2, F^2, B^2> */
    bool finished_phase2(BasicCube3 &n);
};

} // end of namespace

#endif
