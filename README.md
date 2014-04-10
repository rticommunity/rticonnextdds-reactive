Rx4DDS
==========

.NET Reactive Extensions Adapter for RTI Connext DDS.

- [Rx4DDS.NET Announcement](http://blogs.rti.com/2014/04/09/reactive-programming-using-rx4dds/)
- Research paper on [Scalable Reactive Stream Processing Using DDS and Rx](http://community.rti.com/paper/scalable-reactive-stream-processing-using-dds-and-rx) 


### Windows Build
Both, Visual Studio C++ and C# compilers are required. Supported versions = VS2012 and VS2013 

1. Git clone this repository.
2. Set NDDSHOME (5.1.0+)
3. Compile csharp\shape_type\ShapeType_type-dotnet4.5.sln using VC++
4. Compile csharp\soccer_type\soccer_type-dotnet4.5.sln using VC++
5. Open and compile csharp\rxdds.sln using Visual C#
6. To generate 64 bit executable, please regenerate the C++ type support files using rtiddsgen.
