Rx4DDS
==========

###Reactive Extensions (Rx) Adapters for RTI Connext DDS

Rx4DDS is a research library that integrates Reactive Extensions (Rx) with RTI Connext DDS in C++11, C#, and JavaScript. Rx and DDS are quite complementary because Rx is based on the Observable-Observer pattern, which is analogous to the publish-subscribe pattern of DDS. Furthermore, the core tenet of Rx composition of operations over values that change over time complements DDS instances, which are data objects that change over time. DDS ensures propagation of changes to the interested remote participants. Consequently, combining Rx with DDS enables a coherent end-to-end distributed asynchronous dataflow architecture for both data distribution (which is performed by DDS) and processing (which is done by Rx). Rx and DDS together support location transparency of dataflow-style programs seamlessly. The resulting applications dramatically simplify concurrency to the extent that it can be simply configured.

###Status
The Rx4DDS adapters are research prototypes. RxJS adapter works with [RTI Connext DDS Node.js Connector](https://github.com/rticommunity/rticonnextdds-connector). The C# codebase also includes an implementation of the [DEBS'13 Grand Challenge](http://www.orgs.ttu.edu/debs2013/index.php?goto=cfchallengedetails) using DDS and Rx.NET.

###Resources
- Rx4DDS [Main Page](http://rticommunity.github.io/rticonnextdds-reactive/)
- CppCon2015 presentation [Reactive Stream Processing in Industrial IoT using DDS and RxCpp](http://www.slideshare.net/SumantTambe/reactive-stream-processing-in-industrial-iot-using-dds-and-rx), [demos](http://rticommunity.github.io/rticonnextdds-reactive/), and [video](https://www.youtube.com/channel/UCMlGfpWw-RUdWX_JbLCukXg)
- DEBS'2015 research paper (newer) [Functional Reactive Stream Processing for Data-centric Publish/Subscribe](https://community.rti.com/paper/reactive-stream-processing-data-centric-publishsubscribe)
- Research paper (older) [Scalable Reactive Stream Processing Using DDS and Rx](http://community.rti.com/paper/scalable-reactive-stream-processing-using-dds-and-rx) 
- Rx4DDS.NET [Announcement](http://blogs.rti.com/2014/04/09/reactive-programming-using-rx4dds/)

