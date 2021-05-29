# otp-ascii
One-Time Pad ASCII Graph Utilities

## otp-ascii-gen
One-time Pad ASCII Quaternion Based Graph Generator

Keys 00, 01, 02, ..., 19: Pseudorandom ASCII Character Sequences 33 to 126, 94 characters in length

Indexes:
  - Horizontal:
      - ab: ASCII Character Sequence, 33 to 126
      - cd: ASCII Character Sequence, 126 to 33
  - Vertical:
      - ac: ASCII Character Sequence, 33 to 126
      - bd: ASCII Character Sequence, 126 to 33
      - xn: ASCII Number Sequence, 0 to 9
      - yn: ASCII Number Sequence, mod 10
      - nn: ASCII Number Sequence, 00 to 93
  - Complex:
      - i: ASCII Character Sequence, 33 through 126, randomly shuffled
      - j: ASCII Character Sequence, 33 through 126, randomly shuffled
      - k: Product of i * j
    
Graph: Pseudorandom 94 by 94 Matrix, ASCII Characters 33 to 126

Hashes:
 - SHA01: SHA 512/256 of Keys 00 through 19; otp-ascii string; epoch timestamp
 - SHA02: SHA 512/256 of Indexes and Graph; otp-ascii string; epoch timestamp
 - SHA03: SHA 512/256 of All Keys, Indexes, and Graph; otp-ascii string; epoch timestamp
 - SHA04: SHA 512/256 of Entire contents of otp-ascii-$(timestamp).txt file, written to otp-ascii-$(timestamp).sha

Example Graph:

![image](https://user-images.githubusercontent.com/22720196/120057348-f0ab6300-c007-11eb-92ae-edb609560261.png)

