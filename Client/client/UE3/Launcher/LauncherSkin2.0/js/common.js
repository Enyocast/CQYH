	<!--*********ÂÖ²¥¹ã¸æÇÐ»»********-->
	var imgs = $(".pics img");
	var img_a = $(".pics a");
	var nums = $(".nums span");
	var m = 0;
	
	function imgs_change(){
		m++;
		if(m>($(img_a).length-1)){
			m=0;
		}
		$(nums).removeClass("new_span");
		$(img_a).hide();
		$(nums).eq(m).addClass("new_span");
		$(img_a).eq(m).fadeIn(400);
	}
	gap = setInterval(imgs_change,3000);
	
	$(nums).each(function(k){
		$(this).mouseover(function(){
			clearInterval(gap);
			$(nums).removeClass("new_span");
			$(img_a).hide();
			$(this).addClass("new_span");
			$(img_a).eq(m).fadeIn(400);
			m = k;
		})
		$(this).mouseout(function(){
			gap = setInterval(imgs_change,3000);
		})
	})
	
	$(img_a).mouseover(function(){
		clearInterval(gap);
	})
	$(img_a).mouseout(function(){
		gap = setInterval(imgs_change,3000);
	})
