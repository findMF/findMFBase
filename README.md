[![Build Status](https://travis-ci.org/findMF/findMFBase.svg?branch=master)](https://travis-ci.org/findMF/findMFBase) [![Project Stats](https://www.ohloh.net/p/findMFBase/widgets/project_thin_badge.gif)](https://www.ohloh.net/p/findMFBase)

findMFBase - find molecular features base functions

==
findMF is a header only libarary with good unit test coverage, hosted at github:

Functionality provided:

C++ versions of R-functions such as:

- range, scale, median,
- seq, cumsum, diff, interpolate, quantiles, scale,
- mean, var, sd, skew, kurtosis and their weighted versions.
- runif, rnorm, dnorm, pnorm, qnorm
- filter
- interpolate : linear, cubic, hermite, cosine
- utility functions : readwritebin, readtable, split, copyif

These functions work with iterators, and are not tied to a specific type of C++ container.
 
The library contains also functionality specific to mass spectrometry:
- re-sampling of ms spectra
- peak detection

upon these algorithms an
- peak picker for qtof data is provided in the library.

findMFBase has an BSD licence.
findMFBase has, one dependency : boost - any version of boost newer than 1.45 should be fine.
The build system used is cmake.

Most of the functionality is covered by unitests.
findMFBase is regularly build and tested with the gcc and clang complier on Travis.

The qtof peak picker provided with and based on this library, was thoroughly evaluated
in the Aebersold Laboratory and compared with other peak pickers on ABSciex QTof data.
It has been shown, and the results will be published soon, that it
outperforms alternative peakpickers on this type of data. The binary version of the qtofpeakpicker can be downloaded and installed from http://proteowizard.sourceforge.net/






