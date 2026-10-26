/********************************************************************
Created:	2013/04/18
Filename: 	HelpTip
file ext:	as
Author:		hemu@snda
Purpose:	Tips系统View HelpTip控件
*********************************************************************/

package ActionScript3.Tips
{

    import flash.display.MovieClip;
    import scaleform.clik.core.UIComponent;
    import flash.text.TextField;
    import scaleform.clik.controls.ListItemTreeRenderer;
    import scaleform.clik.controls.Button;
    import flash.events.MouseEvent;
    import flash.external.ExternalInterface;

    public class HelpTip  extends MovieClip
    {
        var tF_ItemName:TextField;
        var mc_NameBg:MovieClip;
        var mc_Prefix:MovieClip;
        var mc_IsEquiped:MovieClip;
        var tF_Color:TextField;
        var mc_ColorBg:MovieClip;
        var tF_Profession:TextField;
        var tF_MainParameter:TextField;
        var tF_Material:TextField;

        var tF_AddParameter:TextField;

        var mc_FootHead:MovieClip;
        var tF_DurationTitle:TextField;
        var tF_Duration:TextField;
        var tF_PriceTitle:TextField;
        var tF_Price:TextField;
        var mc_MoneyType:MovieClip;
        var tF_LevelTitle:TextField;
        var tF_Level:TextField;

        var mc_TipAid:MovieClip;

        var mc_Bg:MovieClip;
		
		public var TipHeight:int;
		public var TipWidth:int;

        public var TipData:HelpTipData;

        public function HelpTip()
        {
            // constructor code
        }

        override protected function configUI():void
        {
            super.configUI();
            Resize();
            setUpdateDataCallBack(updateData);
        }

        function updateData( data:Object ):void
        {
            TipData = data as HelpTipData;
            if ( TipData )
            {
                visible = true;

                tF_ItemName.text        =  TipData.ItemName ;
                mc_IsEquiped.visible    =  TipData.IsEquiped;
                tF_Color.text           =  TipData.ColorName ;
                tF_MainParameter.text   =  TipData.MainParameter ;
                tF_AddParameter.text    =  TipData.AddParameter ;
                tF_Duration.text        =  String( TipData.Duration );
                tF_Price.text           =  String( TipData.Price );
                tF_Level.text           =  String( TipData.Level );

                mc_NameBg.gotoAndStop( TipData.ItemType );
                tf_Prefix.gotoAndStop( TipData.PrefixType );
                mc_ColorBg.gotoAndStop( TipData.ColorType );
                mc_MoneyType.gotoAndStop( TipData.MoneyType );
                mc_TipAid.gotoAndStop( TipData.TipAid );
            }
            else
            {
                visible = false;
            }
            Resize();
        }

        function Resize()
        {
            var newHeight:int = tF_AddParameter.height;
            mc_FootHead.y +=  newHeight;

            tF_DurationTitle.y +=  newHeight;
            tF_Duration.y +=  newHeight;
            tF_PriceTitle.y +=  newHeight;
            tF_Price.y +=  newHeight;
            mc_MoneyType.y +=  newHeight;
            tF_LevelTitle.y +=  newHeight;
            tF_Level.y +=  newHeight;
            mc_TipAid.y +=  newHeight;

            mc_Bg.height = mc_TipAid.y - mc_Bg.y + 7;
        }
    }

}