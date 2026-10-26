jQuery.fn.sSelect = function(){
	var selectId = $(this).attr('id');
	var selectIndex;
	$('#'+selectId).append('<div class="dropselectbox"><h4></h4><ul style="display:none"></ul></div>');
	$.each($('#'+selectId+' > select > option'), function(i){
		if ($(this).attr("selected") == true){
			$('#'+selectId+' > div > h4').empty().append($(this).text());
		}
	});
	$('.dropselectbox').show();
	$('#'+selectId+' > select').hide();
	$('#'+selectId).mousedown(function(e){
		e.stopPropagation();
	});
	$('#'+selectId).bind("click",function(e){
		selectId = $(this).attr('id');
		if($('#'+selectId+' > div > ul').css("display") == 'block'){
			$('.dropselectbox > ul').empty().hide();
			$('.dropselectbox > h4').removeClass("over");
		}else{
			$('#'+selectId+' > div > ul').empty().toggle();
			$('#'+selectId+' > div > h4').toggleClass("over");
			setSelectValue(selectId);
			//select option
			$('#'+selectId+' > div > ul > li').click(function(e){
					selectIndex = $('#'+selectId+' > div > ul > li').index($(this)[0]);
					$('#'+selectId+'> select')[0].selectedIndex = selectIndex;
					$('#'+selectId+' > select')[0].onchange();
					setSelectValue(selectId);
					cleadMenu();
					e.stopPropagation();
			})
			.hover(
					function(){
						$('#'+selectId+' > div > ul > li').removeClass("over");
						$(this).addClass("over");
					},
					function(){
						$(this).removeClass("over");
					}
			);
			$(document).bind("click",cleadMenu);
		}
		e.stopPropagation()
	})
	.bind("selectstart",function(){
		return false;
	})
	.bind("blur",function(){
		cleadMenu();						  
	});
}

function cleadMenu(){
	$('.dropselectbox > ul').empty().hide();
	$('.dropselectbox > h4').removeClass("over");	
	$(document).unbind("click",cleadMenu);
}

function setSelectValue(sID){
	$.each($('#'+sID+' > select > option'), function(i){
		$('#'+sID+' > div > ul').append("<li>"+$(this).text()+"</li>");
		if ($(this).attr("selected") == true){
			$('#'+sID+' > div > h4').empty().append($(this).text());
			$('#'+sID+' > div > ul > li').eq(i).addClass("over").addClass("selectedli");
		}
	});
} 