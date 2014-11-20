Rx4DDS
==========

.NET Reactive Extensions Adapter for RTI Connext DDS.

- Rx4DDS.NET [Announcement](http://blogs.rti.com/2014/04/09/reactive-programming-using-rx4dds/)
- Research paper (newer) [Functional Reactive Stream Processing for Data-centric Publish/Subscribe Systems](http://community.rti.com/paper/functional-reactive-stream-processing-data-centric-publishsubscribe-systems)
- Research paper (original) [Scalable Reactive Stream Processing Using DDS and Rx](http://community.rti.com/paper/scalable-reactive-stream-processing-using-dds-and-rx) 
- Reactive Stream Processing using DDS and Rx [presentation](http://www.slideshare.net/SumantTambe/reactive-stream-processing-using-dds-and-rx)
- 2014 Silicon Valley Code Camp [video](https://vimeo.com/108753792)


### Windows Build
Both, Visual Studio C++ and C# compilers are required. Supported versions = VS2012 and VS2013 

1. Git clone this repository.
2. Get [RTI Connext DDS](http://www.rti.com/products/dds/).
3. Set NDDSHOME (5.1.0+)
4. Compile csharp\shape_type\ShapeType_type-dotnet4.5.sln using VC++
5. Compile csharp\soccer_type\soccer_type-dotnet4.5.sln using VC++
6. Open and compile csharp\rxdds.sln using Visual C#
7. To generate 64 bit executable, please regenerate the C++ type support files using rtiddsgen.
