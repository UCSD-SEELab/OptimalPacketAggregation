# PacketAggregation
Optimal Packet Aggregation for Wireless Networks
This code defines multiple transmission manager implementations, including our optimal versions. The user doesn't have to change the code, unless a new implementation is required. Please use the configuration files to implement scenarios.

Structure
The code structure consists of TransmissionManager classes that control the aggregation times of each node. Each manager has multiple Application class instances defining data streams. Every Application has a DeadlineProcess for deadline assignments, a GenerationProcess for data generation and a GainFunction for optimization purposes. Also, each TransmissionManager has a Packet level GainFunction that is applied to all Application instances. The user can implement more GainFunction algorithms, DeadlineProcess and GenerationProcess codes. The GainConfigureHelper, GenerationConfigureHelper and DeadlineConfigureHelper must be updated accordingly.

Contact
For any bugs, suggestions or copy/modification/usage requests, email me at aakyurek@ucsd.edu. This code has been implemented by Alper Sinan Akyurek in part as an NSF project. Please provide proper citation if you will be using any part of the code.
