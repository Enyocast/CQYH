package ActionScript3.Common.Utils {
	import flash.display.Shader;
	import flash.filters.BevelFilter;
	import flash.filters.ColorMatrixFilter;
	import flash.filters.DropShadowFilter;
	import flash.filters.GlowFilter;
	import flash.text.TextFormat;
	import flash.text.TextFormatAlign;
	
	public class StyleType {

        private static var _instance:StyleType;
		public function StyleType() {
			// constructor code
		}
		
		public static function getInstance():StyleType
		{
			if(_instance==null){
				_instance=new StyleType();
			}
			return _instance;
		}
		/**
		 * 获取斜角滤镜
		 * @return 
		 * 
		 */
		public function getBevel():BevelFilter
		{
			 var bevel:BevelFilter=new BevelFilter(5,45,0xffffff,1,0xFFF9F2,1,5,5,1,1,"inner",true);
			 
			 return bevel;
		}
		
		/**
		 * 获取投影滤镜 
		 * @return 
		 * 
		 */		
		public function getDropShadow():DropShadowFilter
		{
			var dropShadow:DropShadowFilter=new DropShadowFilter();
			return dropShadow;
		}
		
		/**
		 * 获取发光滤镜 
		 * @return 
		 * 
		 */		
		public function getGlow():GlowFilter
		{
			var glow:GlowFilter=new GlowFilter(0xffffff,1,2,2,1,1,false,false);
			return glow;
		}
		
		/**
		 * 获取黑白滤镜 
		 * @return 
		 * 
		 */		
		public function getBlackFilter():ColorMatrixFilter
		{
			var matrix:ColorMatrixFilter=new ColorMatrixFilter([0.33,0.33,0.33,0,0,0.33,0.33,0.33,0,0,0.33,0.33,0.33,0,0,0,0,0,1,0]);
			return matrix;
		}
		
		/**
		 * Get gray filter for disabled state.
		 * @return 
		 * 
		 */		
		public function getGrayFilter():ColorMatrixFilter
		{
			var matrix:ColorMatrixFilter = new ColorMatrixFilter(ConfigConstants.MATRIX_OF_GRAY_FILTER);
			return matrix;
		}
		
		/**
		 * 获取文本样式 
		 * @return 
		 * 
		 */		
		public function getFormat():TextFormat
		{
			var format:TextFormat=new TextFormat("",13,0xffffff,true,null,null,null,null,TextFormatAlign.CENTER);
			return format;
		}

	}
	
}
