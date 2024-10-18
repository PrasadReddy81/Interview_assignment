## Time and Space Complexity Analysis.
1. Reading Data from Files:
  * Each iteration processes a line from each file. This results in a time complexity of O(n), where n is the number of rows (samples). If there are 1,000,000 samples, the complexity will scale linearly.
  * Space complexity for file reading is O(1) as no extra space is required beyond storing a single line at a time.
2. Keyboard Input Processing:
  * Since the program constantly listens for keyboard inputs while processing data, the time complexity for this part is O(1) per input.
  * Space complexity for storing input is O(1).
3. Synchronization Overhead:
  * The use of mutex for synchronization adds constant overhead, but it does not affect the overall complexity, remaining at O(1) for both time and space.

## Execution Latency
1. The latency for processing the data and responding to steering input will depend on:
  * The time taken to read each file line, which can be simulated as O(1) for each iteration.
  * The time for processing keyboard inputs, which is near-instantaneous (approximately O(1)).
