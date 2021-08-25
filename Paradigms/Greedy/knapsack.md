# Fractional Knapsack 🎒

## Safe Move
There exists an optimal solution that uses as much as possible of an item with the maximal value per unit of weight. 

## Greedy Algorithm 
- While knapsack is not full: 
    - Choose item i with maximum value/weight
    - If items fits into knapsack, take all of it
    - Otherwise, take so much as to fill the knapsack 
- Return total value and amounts taken

## Optimization 
- Sort items by decreasing value/weight
- Knapsack after sorting is O(n)
- Sort + Knapsack is O(n log n)