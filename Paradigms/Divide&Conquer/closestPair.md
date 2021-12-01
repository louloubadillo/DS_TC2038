# Closest pair of points 🔴→🔵

## Strategy 
- Divide: Draw vertical line L so that n/2 points on each side
- Conquer: Find closes pair in each side recursively
- Combine: Find closes pair with one point in each side
- Return best of 3 solutions

## Optimization 
Find closest pair with one point in each side, assuming that distance < δ

- Observation: Suffices to consider only those points within δ of line L 
- Sort points in 2 δ-strip by their y-coordinate
- Check distances of only those points within 7 positions in sorted list