/*
 * SDG game website plugin
 * author: Michael Xu
 * Date: 2010-08-11 (Wednesday, 11 August 2010)
 * Revision: 1.0
 */

/*-----------------------*/
/*--------选项卡1  -------*/
/*-----------------------*/
;(function($){
	$.fn.extend({
		"xzwTab_1":function(tabList, tabCont,options){
			var _id = $(this).attr("id");
			var _tabList = $(this).find(tabList);
			var _tabCont = $(this).find(tabCont);
			
			var _tabElem = _tabList.find("li");
			var settings = $.extend({
				currentTab:0,
				defaultClass:"Current"
			},options);
			
			_tabList.find("li:eq("+ settings.currentTab +")").addClass(settings.defaultClass);
			_tabCont.children("div").each(function(i){
				$(this).attr("id", _id + "_info_" + i);
			}).eq(settings.currentTab).css({"display":"block"});
			
			_tabElem.each(function(i){
				$(_tabElem[i]).click(
					function(){
						if($(this).className != settings.defaultClass){
							$(this).addClass(settings.defaultClass).siblings().removeClass(settings.defaultClass);
						}
						_tabCont.children("div").eq(i).css({"display":"block"}).siblings().css({"display":"none"});
					}					 
				);				   
			});
		}			
	});		   
})(jQuery);

/*-----------------------*/
/*--------选项卡2  -------*/
/*-----------------------*/
jQuery.fn.xzwTab_2 = function(tabList,tabMore,tabTxt,options){
	var _tabList = jQuery(this).find(tabList);
	var _tabMore = jQuery(this).find(tabMore);
	var _tabTxt = jQuery(this).find(tabTxt);
	
	//为了简化操作，强制规定选项卡必须用li标签实现
	var tabListLi = _tabList.find("li");
	var defaults = {currentTab:0,defaultClass:"Current"};
	var o = jQuery.extend({},defaults,options);
	_tabList.find("li:eq("+o.currentTab+")").addClass(o.defaultClass);
	var _defaultURL = _tabList.find("li:eq("+o.currentTab+")").children("span").attr("rel");
	jQuery("a",_tabMore).attr("href", _defaultURL);
	
	//强制规定内容层必须以div来实现
	_tabTxt.children("div").each(function(i){
		jQuery(this).attr("id","div"+i);						  
	}).eq(o.currentTab).css({"display":"block"});
	
	tabListLi.each(
		function(i){
			jQuery(tabListLi[i]).click(
				function(){
					var _url = jQuery("span",this).attr("rel");
					//alert(_url);
					if(jQuery(this).className != o.defaultClass)
					{
						jQuery(this).addClass(o.defaultClass).siblings().removeClass(o.defaultClass);
					}
					_tabTxt.children("div").eq(i).css({"display":"block"}).siblings().css({"display":"none"});
					jQuery("a",_tabMore).attr("href", _url);
					//alert(jQuery("li",_tabMore).html())
				}
			)
		}
	);
	return this;
};

/*-----------------------*/
/*--------选项卡3  -------*/
/*-----------------------*/
;(function($){
	$.fn.extend({
		"switchBgImg":function(tabList,moresElem,options){
			var settings = $.extend({
				currentTab:0,
				currentCss:"Current"
			},options);
			var _parentElem = $(this);
			var _tabList = $(this).find(tabList);
			var _tabListLi = _tabList.find("li");
			var _moreLink = $(this).find(moresElem);
			var _currentElem = _tabList.find("li:eq("+ settings.currentTab + ")");
			_currentElem.addClass(settings.currentCss);
			var _currentURL = _currentElem.children("a").attr("href");
			var _bgImgURL = _currentElem.children("a").attr("rel");
			_moreLink.attr("href", _currentURL);
			_currentBgImg = "url("+ _bgImgURL + ") 0 0 no-repeat";
			_parentElem.css({"background": _currentBgImg});
			
			_tabListLi.each(function(i){
				$(_tabListLi[i]).click(
					function(){
						var _currentURL = $(this).children("a").attr("href");
						var _bgImgURL = $(this).children("a").attr("rel");
						if($(this).className != settings.currentCss){
							$(this).addClass(settings.currentCss).siblings().removeClass(settings.currentCss);
						}
						_moreLink.attr("href", _currentURL);
						_currentBgImg = "url("+ _bgImgURL + ") 0 0 no-repeat";
						_parentElem.css({"background": _currentBgImg});
					}					 
				);				   
			});

		}		
	});	   
})(jQuery);


/*-----------------------*/
/*--------轮播图片-------*/
/*-----------------------*/
;(function($){
	$.fn.extend({
		"xzwTransformView":function(imgArr,numArr,msgArr,options){
			var settings = $.extend({
				imgHeight: "100px",
				delay: 1000
			},options);
			var _elem = $(this);
			var _lenMax = $("li", numArr).length;
			var _index = 0;
			
			var _imgArr = $(this).find(imgArr);
			var _numElem = $(this).find(numArr);
			var _msgArr = $(this).find(msgArr);
			
			$("li", _imgArr).eq(0).css("display","block");
			_numElem.eq(0).addClass("active");
			$("li", _msgArr).eq(0).fadeIn("fast");
			
			$("li",_numElem).mouseover(function(){
				_index = $("li",_numElem).index(this);
				showImg(_index);
			});
			
			_elem.hover(function(){
					if(_timer){clearInterval(_timer);}
				},
				function(){
					_timer = setInterval(function(){
						showImg(_index);
						_index++;
						if(_index == _lenMax){_index = 0;}
					},settings.delay);
				}
			);
			
			var _timer = setInterval(function(){
				showImg(_index);
				_index++;
				if(_index == _lenMax){ _index = 0;}
				},settings.delay);
			/*
			function showImg(i){
				var _height = parseInt(settings.imgHeight);
				$(imgArr).stop(true,false).animate({top : -_height*i},1000);
				$("li", numArr).eq(i).addClass("active").siblings().removeClass("active");
			}
			*/
			function showImg(i){
				$("li",_imgArr).eq(i).fadeIn("slow").siblings().hide();
				$("li",_msgArr).eq(i).fadeIn("fast").siblings().hide();
				$("li", _numElem).eq(i).addClass("active").siblings().removeClass("active");
			}
			
		}			
	});		   
})(jQuery);

/*-----------------------*/
/*--------锚点跳转-------*/
/*-----------------------*/
;(function($){
	$.fn.extend({
		"anchorGoWhere":function(options){
			var settings = $.extend({target:0, timer:1000},options);
			var _anchor = $(this);
			_anchor.each(function(i){
				$(this).click(function(){
					//alert($(this).html());
					var _rel = $(this).attr("href").substr(1);
					switch(settings.target){
						case 1: 
							var _targetTop = $("#"+_rel).offset().top;
							$("html,body").animate({scrollTop:_targetTop},settings.timer);
							break;
						case 2:
							var _targetLeft = $("#"+_rel).offset().left;
							$("html,body").animate({scrollLeft:_targetLeft},settings.timer);
							break;
					}
					return false;
				});					  
			});
		}			
	});
})(jQuery);


/*-----------------------*/
/*-下拉菜单二级菜单横向定位-*/
/*-----------------------*/
;(function($){
	$.fn.extend({
		"setMenuOptions":function(options){
			var settings = $.extend({
				left:  "0"
			},options);
			this._left  = settings.left;
			$(this).css({"width":"1000"});
			$("div",this).eq(0).css("margin-left",this._left+"px");
		}			
	});		   
})(jQuery);

/*-----------------------*/
/*--------下拉菜单-------*/
/*-----------------------*/
;(function($){
	$.fn.extend({
		"dropDownMenu_xzw":function(){
			var _elem = $(this).children("li:has(div.Lv2Box)");
			_elem.hover(
				function(){
					$(this).find("div.Lv2Box").stop(true,true).slideDown(400);
				},
				function(){
					$(this).find("div.Lv2Box").stop(true,true).slideUp("fast");
				}
			);
			
		}			
	});		   
})(jQuery);


/*-----------------------*/
/*--------toolTip -------*/
/*-----------------------*/
;(function($){
	$.fn.extend({
		xzwAlertPlug:function(title,alertOffset){
			var x = y = alertOffset;
			$(this).mouseover(function(e){
				this.myTitle = this.title;
				this.title = "";
				var toolTip = "<div class='toolTip'>"+ this.myTitle +"</div>";
				$("body").append(toolTip);
				$(".toolTip").css({"top":(e.pageY + y)+"px","left":(e.pageX + x)+"px", "visibility":"visible"}).show("fast");
			}).mouseout(function(){
				this.title = this.myTitle;
				$(".toolTip").remove();
			}).mousemove(function(e){
				$(".toolTip").css({"top":(e.pageY + y)+"px","left":(e.pageX + x)+"px"});
			})
			return this;
		}			
	});
})(jQuery);


/*-----------------------*/
/*--------accordion：leftMenu -------*/
/*-----------------------*/
;(function($){
	$.fn.extend({
		"xzwAccordion_1":function(options){
			settings = $.extend({targetA:null, current:null}, options);
			var _elem = $(this);
			var a_1_Arr = $("li:has(dl)",_elem).children("a");
			var _currentTitle = $("#"+settings.targetA, _elem).find("a");
			//alert(_currentTitle.html());
			var _ddArr = _currentTitle.next("dl").children("dd");
			_currentTitle.next("dl").slideDown(500);
			$(_ddArr[settings.current-1]).addClass("Current");
			
			a_1_Arr.toggle(function(){
				$(this).next("dl").slideDown(500);
				return false;
				},
				function(){
					$(this).next("dl").slideUp(500);
					return false;
				}
			);
		}
	});
})(jQuery);

;(function($){
	$.fn.extend({
		"pullDownMenu":function(onClickElem,pullDownElem){
			var _elem = $(this);
			var _onClickElem = $(this).find(onClickElem);
			var _pullDownElem = $(this).find(pullDownElem);
			_onClickElem.toggle(
				function(){
					_pullDownElem.slideDown("slow");	
				},
				function(){
					_pullDownElem.slideUp(500);
				}
			);
		}			
	});		   
})(jQuery);

;(function(){
	$.fn.extend(
		{
			"allCheck":function(allCheckBtn, checkboxRow, options){
				var settings = $.extend({checkboxName:null},options);
				var _checkBoxs = $(this).find(":checkbox[name="+settings.checkboxName+"]");
				var _rows = $(checkboxRow).find("tbody>tr");
				var _allCheckBtn = $(allCheckBtn);
				var _relvalue = null;
				
				_allCheckBtn.click(function(){
					_checkBoxs.add(_allCheckBtn).attr("checked",this.checked);							
				});
				/*
				_rows.click(function(){
					$(this).find(":checkbox").attr("checked",!$(this).find(":checkbox").get(0).checked);		
					_allCheckBtn.attr("checked", _checkBoxs.size()== _checkBoxs.filter(":checked").size());
				});
				*/
				_checkBoxs.click(function(){
					//e.stopPropagation();
					_allCheckBtn.attr("checked", _checkBoxs.size()== _checkBoxs.filter(":checked").size());
				});
			}
		}	
	);		   
})(jQuery);


jQuery(document).ready(function(){
	jQuery("#newsCenter").xzwTab_1(".tagMenu",".tagContent");
	jQuery("#role").xzwTab_1(".tagMenu",".tagContent");
	jQuery("#xcyh").xzwTab_2(".tagMenu",".more",".tagContent");
	jQuery("#xmhd").xzwTab_2(".tagMenu",".more",".tagContent");
	jQuery("#media").xzwTab_2(".tagMenu",".more",".tagContent");
	jQuery("#community").xzwTab_2(".tagMenu",".more",".tagContent");
	jQuery("#webSite").xzwTab_2(".tagMenu",".more",".tagContent");
	jQuery("#news_tab").xzwTab_2(".tagMenu",".more",".tagContent");
	jQuery("#list_1").pullDownMenu("h2","dl");
	jQuery("#list_2").pullDownMenu("h2","dl");
	jQuery("#scrolAD").xzwTransformView("#slider1","#numList",null,{delay:3000});
	jQuery("#goTop").anchorGoWhere({target:1});
	jQuery("#zhiye").switchBgImg(".tagMenu",".moreLink");
	jQuery("#allcheck2").allCheck("#allCheckBtn2","#downFiles2",{checkboxName:"dfile2"});
});

