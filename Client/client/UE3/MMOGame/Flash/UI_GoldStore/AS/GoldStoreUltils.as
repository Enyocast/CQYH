package UI_GoldStore.AS
{
	/**
	 * 客户端下发的数据是以点券为单位的，UI界面显示又以元宝或者RMB为单位进行显示，100点券 = 1 元宝 
	 * @author wangpenghe.phil
	 * 
	 */	
	public class GoldStoreUltils
	{
		public static const GOLD_TO_COUPON_RATE:int = 100;
		public static const CASH_TO_COUPON_RATE:int = 1000;
		public static const UNIT_PRICE_CHANGED_STEP_VALUE:int = 1;
		
		public static const MONEY_TYPE_GOLD:int    = 1;
		public static const MONEY_TYPE_RMB:int     = 2;
		
		public static const EXCHANGE_TYPE_BUY:int  = 1;
		public static const EXCHANGE_TYPE_SELL:int = 2;
		
		public static const MONEY_UNIT_HUNDERD_MILLION:String = "亿";
		public static const MONEY_UNIT:String = "万";
		
		private static const HUNDRED_MILLION:int = 100000000;
		private static const TEN_THOUSAND:int    = 10000;
		
		public static function couponToGold(couponValue:int, bformat:Boolean = true):String
		{
			var formatValue:Number = couponValue / GOLD_TO_COUPON_RATE;
			if(bformat)
			{
				return formatNumString(formatValue, MONEY_TYPE_GOLD);
			}
			return formatValue.toFixed(2);
		}
		
		public static function couponToCash(couponValue:int, bformat:Boolean = false):String
		{
			var formatValue:Number = couponValue / CASH_TO_COUPON_RATE;
			if(bformat)
			{
				return formatNumString(formatValue, MONEY_TYPE_RMB);
			}
			return 	formatValue.toFixed(2);
		}
		
		//不能截断，因为存在String“6.6”转换成 Number = 6.59999999的情况，此时需要四舍五入取整
		public static function goldToCoupon(goldValue:Number):int
		{
			return Math.round(goldValue * GOLD_TO_COUPON_RATE);
		}
		
		public static function cashToCoupon(cashValue:Number):int
		{
			return Math.round(cashValue * CASH_TO_COUPON_RATE);
		}
		
		public static function formatNumString(num:Number, moneyType:int = -1):String
		{
			var res:String = "";
			if( num >= TEN_THOUSAND )
			{
				if(num >= HUNDRED_MILLION)
				{
					res += Math.floor(num / HUNDRED_MILLION).toString();
					res += MONEY_UNIT_HUNDERD_MILLION;
				}
				if(num % HUNDRED_MILLION >= TEN_THOUSAND)
				{
					res += Math.floor(num % HUNDRED_MILLION / TEN_THOUSAND).toString();
					res += MONEY_UNIT;
				}
			}
			if(num % TEN_THOUSAND > 0 || num == 0)
			{
				if(moneyType == MONEY_TYPE_GOLD)
				{
					res += couponToGold(goldToCoupon(num % TEN_THOUSAND), false);//小数%运算后需要重新格式化数据
				}
				else if(moneyType == MONEY_TYPE_RMB)
				{
					res += couponToCash(cashToCoupon(num % TEN_THOUSAND), false);//小数%运算后需要重新格式化数据
				}
				else
				{
					res += (num % TEN_THOUSAND);
				}
			}
			return res;
		}
	}
}