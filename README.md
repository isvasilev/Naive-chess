# Naive-chess
Chess engine that suports thr UCI protocol.
Note: suports only search with time controls (no nodes , depths ect.) 
Also currently hash size is not implemented as option 
but will try to allocate 1024Mb for the hash when started.

Description of the engine:

  1. Board representation: 
   - array[256] (16x16); 
   - piece list;
   - pseudo-legal move generation;
  
  2. Search:
   - main search is basic alpha beta;
   - iterative deepening;
   - quiescence search with delta pruning;
   - transposition table (alway replace) used in the main search;
   - move ordering - hash move then mvv - lva;
   
  3. Evaluation:
   - material;
   - piece-square tables;
   - king pawn shield;
  
  
