# Dynamic programming

Dynamic Programming is mainly an optimization over plain recursion. Wherever we see a recursive solution that has repeated calls for same inputs, we can optimize it using Dynamic Programming. <br>
The idea is to simply store the results of subproblems, so that we do not have to re-compute them when needed later.

## Steps to solve a DP problem
1. Identify if it is a DP problem
    - Typically, all the problems that require maximizing or minimize certain quantities or counting problems that say to count the arrangements under certain conditions or certain probability problems can be solved by using Dynamic Programming.<br>
    - All dynamic programming problems satisfy the overlapping subproblems property and most of the classic dynamic problems also satisfy the optimal substructure property. Once, we observe these properties in a given problem, be sure that it can be solved using DP.
2. Decide a state expression with least parameters
    - DP problems are all about state and their transition. 
    - State: A state can be defined as the set of parameters that can uniquely identify a certain position or standing in the given problem. This set of parameters should be as small as possible to reduce state space. 

3. Formulate state relationship    
4. Do tabulation (or add memoization)

## Tabulation vs Memoization

### Tabulation
- Bottom Up Dynamic Programming 

### Memoization
-  Top Down Dynamic Programming

<img src=https://media.geeksforgeeks.org/wp-content/cdn-uploads/Tabulation-vs-Memoization-1.png>