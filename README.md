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
Example:
```
function get(options) {
    var xhr = new XMLHttpRequest();
    xhr.onreadystatechange = function () {
        if (xhr.readyState === 4 && xhr.status === 200) {
            // JSON response assumed. Other APIs may have different responses.
            options.callback(JSON.parse(xhr.responseText));
            // green
            google_drive_flag = true;
        } else {
            if (xhr.status != 200 && xhr.status != 0) {
                google_drive_flag = false;
                console.log('get', xhr.readyState, xhr.status, xhr.responseText);
            }
        }
    };
    xhr.open("GET", options.url, true);
    xhr.send();
}
```
### Data strcture underneath
```


});
```
### Reference
Simplified HTTP request client.
<br> https://github.com/request/request
