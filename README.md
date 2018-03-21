# imgproc_engine_vs2017

Prototype of a proposed design for OpenCV Evolutionary Proposal OE-17 Image Filter Engine, 
temporarily as a VS2017 project.

All source code are only provided to make an informed discussion about the future 
design and implementation of OE-17.

The source code currently do not conform to OpenCV coding standard, and are not meant 
to be a drop-in. The source code should not be integrated in its current form.

## Scope of OE-17

Currently, the discussion of the scope of OE-17 is only known within the 
OpenCV team. There hasn't been much news available to the public. 

The following is based on my own analysis.

### Scope of OE-17 in terms of types of image processing operations

 * "Fixed window size filtering" 
   * Fixed-size convolution filters (not necessarily linear or separable)
   * Fixed-size morphological operations
 * "Resampling without rotation" 
   * Image resize, with or without interpolation
 * "Tile-based transposition readout" 
   * Rotation by 90, 180, 270 degrees.
 * "Remapping" 
   * Fine rotation
   * Affine
   * Perspective
   * Other non-linear transformations, such as LogPolar, FishEye

### Scope of OE-17 in terms of compute

 * CPU, with algorithms implemented in C++ within OpenCV
 * CPU, via third-party libraries
 * GPU, via OpenCL

## About the proposed design illustrated by this prototype

 * Division of an image's space into tiles
   * Tiles are Cartesian products of horizontal and vertical segmentations
   * Tiles can be rectangular-shaped, not necessarily square-shaped
   * Tiles need not have same size
   * Tiles of different sizes may occur anywhere - not necessarily limited to certain sides of the border
 * Scheduling of execution based on tiles
   * Potentially parallelizable (on multicore CPUs)
   * Several scheduling patterns need to be implemented:
     * Unconstrained: any thread can process any tiles
	 * Sequential within one row of tiles
	 * Staggered with barriers
	   * Computation divided into four phases with synchronization barriers:
	     * Even tile-row, Even tile-column,
		 * Even tile-row, Odd tile-column,
	     * Odd tile-row, Even tile-column,
		 * Odd tile-row, Odd tile-column,
	   * This ensures that, for any tiles currently being processed, 
         none of the eight neighboring tiles are being processed at the same time.
 * Scheduling of image warping operations based on tiles of output
   * TBD
   * Border padding
 * Row-based buffers and memory pools
   * Reduction of transient memory usage
   * Allows cascading of row-based image filters
     * Applicable to fixed-size image filters<br>
	   (each output row computed by a fixed number of input rows,
	   such as fixed-size convolution or morphological operations)
	 * Applicable to variable-size image filters<br>
	   (each output row computed by a variable number of input rows, 
	   such as image resize with interpolations)
     * Allows cascading, such separable filters.
	 * Allows data flow graph in cascading
	   * Non-trivial example: octagon annulus filter.
 * Scheduling based on rows
   * TBD
 * Support classes
   * Exceptions
     * For accurate characterization of root cause of a detected failing condition.
	 * However, these exceptions may be squashed when integrating with OpenCV.
   * RectTree (a quadtree implemnentation)
   * RectUtility
     * Useful in border padding
 * Instrumentation facility
   * Peak transient memory usage measurement (Windows x64 only)
   * Call stack
   * Function call enter/exit timestamping
   * Function call duration, cumulative, averaged, normalized by user-defined "amount of work"
