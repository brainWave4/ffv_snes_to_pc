# Notes
* Bit represents the bit depth of a texture.
* Width is by number of bytes times bit depth. At 1 bit depth, a byte contains 8 pixels.
* A tile is sized 8 x 8 pixels-squared.
* A tileset is usually 16 tiles wide.

# List

|Content|From|To|Total Bytes|in Dec|Bit|Width|Height|in Tiles
|---|---|---|---|---|---|---|---|-
|Map Overlay|C0/DF00|CF/E4FF|$F0600|984576|1|16|61536|7692
|Big Fonts|C3/EB00|C3/FDFF|$1300|4864|1|16|304|38
|Small Fonts|D1/F000|D1/FFFF|$1000|4096|2|32|128|16
|Kanji|DB/D000|DB/F7FF|$2800|10240|1|16|640|80