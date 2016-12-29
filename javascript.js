function calc_zscore(data) {
	var xix0=[];
	for (var i=0; i<data.features.length; i++) {
		xix0.push((2015-Number(data.features[i]["properties"]["time"])));
	}
	var xix=d3.sum(xix0);
	var X=xix/data.features.length;
	var xix2=[];
	for (var i=0; i<data.features.length; i++) {
		xix2.push(Math.pow((2015-data.features[i]["properties"]["time"]),2));
	}
	var S=Math.sqrt(d3.sum(xix2)/data.features.length-Math.pow(X,2));
	for (var y=0; y<data.features.length; y++) {
		var gert_xix=[];
		var gert_xix_=[];
		var gert_weight=[];
		for (var i=0; i<data.features.length; i++) {
			var hav0=haversineDistance(data.features[i]["geometry"]["coordinates"], data.features[y]["geometry"]["coordinates"]);
			if (hav0<=15) {
				var hav=1;
			} else {
				var hav=0;
			}
			gert_xix.push(hav*(2015-Number(data.features[i]["properties"]["time"])));
			gert_xix_.push(Math.pow(hav,2));
			gert_weight.push(hav);
		}
		var gert=(d3.sum(gert_xix)-X*d3.sum(gert_weight))/(S*Math.sqrt(Math.abs((data.features.length*d3.sum(gert_xix_)-Math.pow(d3.sum(gert_weight),2)))/(data.features.length-1))); 
		data.features[y]["properties"]["zscore"]=gert;
	}
	return data;
}

function haversineDistance(coords1, coords2) {
	function toRad(x) {
		return x * Math.PI / 180;
	}

	var lon1 = coords1[0];
	var lat1 = coords1[1];

	var lon2 = coords2[0];
	var lat2 = coords2[1];

	var R = 6378.137; // km                                                                                                                                                                  
	var x1 = lat2 - lat1;
	var dLat = toRad(x1);
	var x2 = lon2 - lon1;
	var dLon = toRad(x2)
	var a = Math.sin(dLat / 2) * Math.sin(dLat / 2) +
	Math.cos(toRad(lat1)) * Math.cos(toRad(lat2)) *
	Math.sin(dLon / 2) * Math.sin(dLon / 2);
	var c = 2 * Math.atan2(Math.sqrt(a), Math.sqrt(1 - a));
	var d = R * c;

	//if(isMiles) d /= 1.60934;                                                                                                                                                              
	return d;
}
