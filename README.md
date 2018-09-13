# Information-Retrival-and-Training
The goal is to read from large CSV/JSON file and train classifier based on that
<br>To be more specific:
<br>Importing data
<br>Cleaning data
<br>Splitting it into train sets/Pre-processing
<br>Calculating 
<br>Make prediction

### User defined type
```
using rowType = std::map<std::string, std::string>;
using countType = std::map<std::string, int>;
using Pair_type = std::pair<std::string, std::string>;

});
```
### Requesting data
```
var request = require('request');
request('URL', function (error, response, body) {
  console.log('error:', error); // Print the error if one occurred
  console.log('statusCode:', response && response.statusCode); // Print the response status code if a response was received
});
```


### Reference
Simplified HTTP request client.
<br> https://github.com/request/request
