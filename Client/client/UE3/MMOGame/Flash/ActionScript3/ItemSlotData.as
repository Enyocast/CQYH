
package ActionScript3 {
	

public class ItemSlotData extends Object
{
	//用于查询用名字，和slot实例名对应，便于查找slot
	public var slotName:String = "";
	
	public var quantity:Number = 1;
	public var iconIndex:Number = -1;
	public var itemtype:String = "";
	public var itemIndex:Number = -1;
	public var iconName:String = "";
	public var itemColor:Number = 0;
	
	public var slotType:Number = -1;
	public var containerID:Number = -1;
	public var slotID:Number = -1;
	
	public var equipID:Number = 0;
	
	public function ItemSlotData() {
		super();		
	}
	
};

}