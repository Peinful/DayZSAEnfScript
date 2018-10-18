//--------------------------------------------------------------------------
class InspectMenuNew extends UIScriptedMenu
{
	private ItemPreviewWidget m_item_widget;
	private int m_characterRotationX;
	private int m_characterRotationY;
	private int m_characterScaleDelta;
	private vector m_characterOrientation;

	
	void InspectMenuNew()
	{
		
	}
	
	//--------------------------------------------------------------------------
	void ~InspectMenuNew()
	{
		GetGame().GetDragQueue().RemoveCalls(this);
	
		delete m_item_widget;
	}
	
	//--------------------------------------------------------------------------
	override Widget Init()
	{
		layoutRoot = GetGame().GetWorkspace().CreateWidgets("gui/layouts/inventory_new/day_z_inventory_new_inspect.layout");
		
		
		return layoutRoot;
	}
	
	//--------------------------------------------------------------------------
	override bool OnClick(Widget w, int x, int y, int button)
	{
		super.OnClick(w, x, y, button);
		
		switch (w.GetUserID())
		{
			case IDC_CANCEL:
				Close();
				return true;
		}
	
		return false;
	}
	
	//--------------------------------------------------------------------------
	void SetItem(EntityAI item)
	{
		if (item)
		{
			UpdateItemInfo(layoutRoot, item);
	
			if (!m_item_widget)
			{
				Widget preview_frame = layoutRoot.FindAnyWidget("ItemFrameWidget");
				if (preview_frame)
				{
					float w;
					float h;
					preview_frame.GetSize(w, h);
					m_item_widget = ItemPreviewWidget.Cast( GetGame().GetWorkspace().CreateWidget(ItemPreviewWidgetTypeID, 0, 0, 1, 1, WidgetFlags.VISIBLE, ARGB(255, 255, 255, 255), 10, preview_frame) );
				}
			}
			
			m_item_widget.SetItem(item);
			m_item_widget.SetView( item.GetViewIndex() );
			m_item_widget.SetModelPosition(Vector(0,0,1));
			
			float x, y;		
			m_item_widget.GetPos(x, y);

			m_item_widget.SetSize( 1.75, 1.75 );
		
			// align to center 
			m_item_widget.SetPos( -0.375, -0.375 );
			
			//m_item_widget.SetModelOrientation
			PPEffects.SetBlurInventory(1);
		}
	}
	
	//--------------------------------------------------------------------------
	override bool OnMouseButtonDown(Widget w, int x, int y, int button)
	{
		super.OnMouseButtonDown(w, x, y, button);
		
		if (w == m_item_widget)
		{
			GetGame().GetDragQueue().Call(this, "UpdateRotation");
			g_Game.GetMousePos(m_characterRotationX, m_characterRotationY);
			return true;
		}
		return false;
	}
	
	//--------------------------------------------------------------------------
	void UpdateRotation(int mouse_x, int mouse_y, bool is_dragging)
	{
		vector o = m_characterOrientation;
		o[0] = o[0] + (m_characterRotationY - mouse_y);
		o[1] = o[1] - (m_characterRotationX - mouse_x);
		
		m_item_widget.SetModelOrientation( o );
		
		if (!is_dragging)
		{
			m_characterOrientation = o;
		}
	}
	
	//--------------------------------------------------------------------------
	override bool OnMouseWheel(Widget  w, int  x, int  y, int wheel)
	{
		super.OnMouseWheel(w, x, y, wheel);
		
		if ( w == m_item_widget )
		{
			GetGame().GetDragQueue().Call(this, "UpdateScale");
			m_characterScaleDelta = wheel ;
		}
		return false;
	}
	
	//--------------------------------------------------------------------------
	void UpdateScale(int mouse_x, int mouse_y, int wheel, bool is_dragging)
	{
		float w, h, x, y;		
		m_item_widget.GetPos(x, y);
		m_item_widget.GetSize(w,h);
		w = w + ( m_characterScaleDelta / 4);
		h = h + ( m_characterScaleDelta / 4 );
		if ( w > 0.5 && w < 3 )
		{
			m_item_widget.SetSize( w, h );
	
			// align to center 
			int screen_w, screen_h;
			GetScreenSize(screen_w, screen_h);
			float new_x = x - ( m_characterScaleDelta / 8 );
			float new_y = y - ( m_characterScaleDelta / 8 );
			m_item_widget.SetPos( new_x, new_y );
		}
	}
	//--------------------------------------------------------------------------
	static void UpdateItemInfo(Widget root_widget, EntityAI item)
	{
		if (!root_widget || !item) return;
	
		Widget panelInfo = root_widget.FindAnyWidget("InventoryInfoPanelWidget");
		if ( panelInfo )
		{
			if ( item.IsInherited( ZombieBase ) || item.IsInherited( Car ) )
			{
				panelInfo.Show( false );
			}
			else
			{
				panelInfo.Show( true );
			}
		}
	
		if ( !item.IsInherited( ZombieBase ) && !item.IsInherited( Car ) )
		{
			InventoryItem iItem = InventoryItem.Cast( item );
			WidgetTrySetText(root_widget, "ItemDescWidget", iItem.GetTooltip());
		}
	
		WidgetTrySetText(root_widget, "ItemNameWidget", item.GetDisplayName());
		UpdateItemInfoDamage(root_widget, item);
		UpdateItemInfoLiquidType(root_widget, item);
		UpdateItemInfoTemperature(root_widget, item);
		UpdateItemInfoWetness(root_widget, item);
		UpdateItemInfoQuantity(root_widget, item);
		UpdateItemInfoWeight(root_widget, item);
		UpdateItemInfoFoodStage(root_widget, item);
	}

	//--------------------------------------------------------------------------
	static void UpdateItemInfoDamage(Widget root_widget, EntityAI item)
	{
		if ( item.IsInherited( ZombieBase ) || item.IsInherited( Car ) ) return;
		
		int damageLevel = item.GetHealthLabel();
		
		switch(damageLevel)
		{
			case ItemManager.STATE_RUINED:
			{
				WidgetTrySetText(root_widget, "ItemDamageWidget", "RUINED", Colors.COLOR_RUINED);
				break;
			}
			case ItemManager.STATE_BADLY_DAMAGED:
			{
				WidgetTrySetText(root_widget, "ItemDamageWidget", "BADLY DAMAGED", Colors.COLOR_BADLY_DAMAGED);
				break;
			}
			
			case ItemManager.STATE_DAMAGED:
			{
				WidgetTrySetText(root_widget, "ItemDamageWidget", "DAMAGED", Colors.COLOR_DAMAGED);
				break;
			}
			
			case ItemManager.STATE_WORN:
			{
				WidgetTrySetText(root_widget, "ItemDamageWidget", "WORN", Colors.COLOR_WORN);
				break;
			}
			
			case ItemManager.STATE_PRISTINE:
			{
				WidgetTrySetText(root_widget, "ItemDamageWidget", "PRISTINE", Colors.COLOR_PRISTINE);
				break;
			}
					
			default:
			{
				WidgetTrySetText(root_widget, "ItemDamageWidget", "ERROR", Colors.COLOR_PRISTINE);
				break;
			}
		}
	
	}
	
	//--------------------------------------------------------------------------
	static void UpdateItemInfoLiquidType(Widget root_widget, EntityAI item)
	{
		if ( item.IsInherited( ZombieBase ) || item.IsInherited( Car ) ) return;
		
		ItemBase item_base = ItemBase.Cast( item );
		
		if( item_base && item_base.GetQuantity() > 0 && item_base.IsBloodContainer() )
		{
			BloodContainerBase blood_container = BloodContainerBase.Cast( item_base );
			
			if( blood_container.GetBloodTypeVisible() )
			{
				string blood_type_name = BloodTypes.GetBloodTypeName(blood_container.GetLiquidType());
				WidgetTrySetText(root_widget, "ItemLiquidTypeWidget", "BLOOD: " + blood_type_name, Colors.COLOR_LIQUID);
			}
			else
			{
				WidgetTrySetText(root_widget, "ItemLiquidTypeWidget", "BLOOD", Colors.COLOR_LIQUID);
			}
		}
		else if( item_base && item_base.GetQuantity() > 0 && item_base.IsLiquidContainer() )
		{
			int liquid_type = item_base.GetLiquidType();
			
			switch(liquid_type)
			{
				case LIQUID_WATER:
				{
					WidgetTrySetText(root_widget, "ItemLiquidTypeWidget", "WATER", Colors.COLOR_LIQUID);
					break;
				}
					
				case LIQUID_RIVERWATER:
				{
					WidgetTrySetText(root_widget, "ItemLiquidTypeWidget", "RIVER WATER", Colors.COLOR_LIQUID);
					break;
				}
					
				case LIQUID_VODKA:
				{
					WidgetTrySetText(root_widget, "ItemLiquidTypeWidget", "VODKA", Colors.COLOR_LIQUID);
					break;
				}
				
				case LIQUID_BEER:
				{
					WidgetTrySetText(root_widget, "ItemLiquidTypeWidget", "BEER", Colors.COLOR_LIQUID);
					break;
				}
				
				case LIQUID_GASOLINE:
				{
					WidgetTrySetText(root_widget, "ItemLiquidTypeWidget", "GASOLINE", Colors.COLOR_LIQUID);
					break;
				}
				
				case LIQUID_DIESEL:
				{
					WidgetTrySetText(root_widget, "ItemLiquidTypeWidget", "DIESEL", Colors.COLOR_LIQUID);
					break;
				}
				
				case LIQUID_DISINFECTANT:
				{
					WidgetTrySetText(root_widget, "ItemLiquidTypeWidget", "DISINFECTANT", Colors.COLOR_LIQUID);
					break;
				}
	
				case LIQUID_SALINE:
				{
					WidgetTrySetText(root_widget, "ItemLiquidTypeWidget", "SALINE", Colors.COLOR_LIQUID);
					break;
				}
				
				default:
				{
					WidgetTrySetText(root_widget, "ItemLiquidTypeWidget", "ERROR", Colors.COLOR_LIQUID);
					break;
				}
			}
		}
		else
		{
			WidgetTrySetText(root_widget, "ItemLiquidTypeWidget", "");
		}
	}
	
	//--------------------------------------------------------------------------
	static void UpdateItemInfoTemperature(Widget root_widget, EntityAI item)
	{
		if ( item.IsInherited( ZombieBase ) || item.IsInherited( Car ) ) return;
		float temperature;
		ItemBase item_base = ItemBase.Cast( item );
		if( item_base )
		{
			temperature = item_base.GetTemperature();
		}
		
		if( temperature != 0)
		{
			WidgetTrySetText(root_widget, "ItemTemperatureWidget",  "~ " + temperature.ToString() +  " CELSIUS", GetTemperatureColor( temperature ) );
		}	
		else
		{
			WidgetTrySetText(root_widget, "ItemTemperatureWidget", "");
		}
	}
	
	//--------------------------------------------------------------------------
	static void UpdateItemInfoWetness(Widget root_widget, EntityAI item)
	{
		if ( item.IsInherited( ZombieBase ) || item.IsInherited( Car ) ) return;
		/*		
		_bagwet = 1;
		if(!isNull (itemParent _item) && (itemParent _item) isKindOf "ClothingBase")then{
		_bagwet = getNumber(configFile >> "cfgVehicles" >> typeOf (itemParent _item) >> "absorbency");
		};
	
		//wetness setting
		if(!isNull (itemParent _item) && _bagwet > 0 && _pwetness > 0)then{
		_wetness=getNumber(_config >> "absorbency") min _pwetness;
		};
		*/
		float wetness = 0;
		
		if ( item.IsInherited(ItemBase) )
		{
			ItemBase item_IB = ItemBase.Cast( item );
			wetness = item_IB.GetWet();
		}
		
		float bagwet = 1;
	
		EntityAI parent = item.GetHierarchyParent();
		if (parent && parent.IsClothing())
		{
			bagwet = parent.ConfigGetFloat("absorbency");
		}
		
		if( wetness < ItemManager.STATE_DAMP )
		{
			WidgetTrySetText(root_widget, "ItemWetnessWidget", "");
		}
		else if( wetness >= ItemManager.STATE_DAMP && wetness < ItemManager.STATE_WET )
		{
			WidgetTrySetText(root_widget, "ItemWetnessWidget", "DAMP", Colors.COLOR_DAMP);
		}
		else if( wetness >= ItemManager.STATE_WET && wetness < ItemManager.STATE_SOAKING_WET )
		{
			WidgetTrySetText( root_widget, "ItemWetnessWidget", "WET", Colors.COLOR_WET );
		}
		else if( wetness >= ItemManager.STATE_SOAKING_WET && wetness < ItemManager.STATE_DRENCHED )
		{
			WidgetTrySetText( root_widget, "ItemWetnessWidget", "SOAKING WET", Colors.COLOR_SOAKING_WET );
		}
		else
		{
			WidgetTrySetText( root_widget, "ItemWetnessWidget", "DRENCHED", Colors.COLOR_DRENCHED );
		}
	}
	
	//--------------------------------------------------------------------------
	static void UpdateItemInfoQuantity(Widget root_widget, EntityAI item)
	{
		if ( item.IsInherited( ZombieBase ) || item.IsInherited( Car ) ) return;
		
		ItemBase item_base = ItemBase.Cast( item );
		if( item_base )
		{
			float item_quantity = item_base.GetQuantity();
			int max_quantity = item.ConfigGetInt("varQuantityMax");
			float quantity_ratio;
			
			if( max_quantity > 0 ) // Some items, like books, have max_quantity set to 0 => division by ZERO error in quantity_ratio
			{
				if( item.ConfigGetString("stackedUnit") == "pc." )
				{
					if( item_quantity == 1 )
					{
						WidgetTrySetText( root_widget, "ItemQuantityWidget", item_quantity.ToString() + " PIECE", Colors.COLOR_DEFAULT );
					}
					else
					{
						WidgetTrySetText( root_widget, "ItemQuantityWidget", item_quantity.ToString() + " PIECES", Colors.COLOR_DEFAULT );
					}		
				}
				else if( item.ConfigGetString("stackedUnit") == "percentage" )
				{
					quantity_ratio = Math.Round( ( item_quantity / max_quantity ) * 100 );
					
					WidgetTrySetText( root_widget, "ItemQuantityWidget", quantity_ratio.ToString() + "% REMAINING", Colors.COLOR_DEFAULT );			
				}
				else if( item.ConfigGetString("stackedUnit") == "g" )
				{
					quantity_ratio = Math.Round( ( item_quantity / max_quantity ) * 100 );
					
					WidgetTrySetText( root_widget, "ItemQuantityWidget", quantity_ratio.ToString() + "% REMAINING", Colors.COLOR_DEFAULT );			
				}
				else if( item.ConfigGetString("stackedUnit") == "ml" )
				{
					quantity_ratio = Math.Round( ( item_quantity / max_quantity ) * 100 );
					
					WidgetTrySetText( root_widget, "ItemQuantityWidget", quantity_ratio.ToString() + "% REMAINING", Colors.COLOR_DEFAULT );
				}
				else if( item.IsInherited( Magazine ) )
				{
					Magazine magazine_item;
					Class.CastTo(magazine_item, item);
					
					if( magazine_item.GetAmmoCount() == 1 )
					{
						WidgetTrySetText( root_widget, "ItemQuantityWidget",  magazine_item.GetAmmoCount().ToString() + " PIECE", Colors.COLOR_DEFAULT );
					}
					else
					{
						WidgetTrySetText( root_widget, "ItemQuantityWidget",  magazine_item.GetAmmoCount().ToString() + " PIECES", Colors.COLOR_DEFAULT );
					}
				}
				else
				{
					WidgetTrySetText( root_widget, "ItemQuantityWidget", "" );
				}
			}
			else
			{
				WidgetTrySetText( root_widget, "ItemQuantityWidget", "" );
			}
		}
	}
	
	//--------------------------------------------------------------------------
	static void UpdateItemInfoWeight(Widget root_widget, EntityAI item)
	{
		if ( item.IsInherited( ZombieBase ) || item.IsInherited( Car ) ) return;
		
		ItemBase item_IB = ItemBase.Cast( item );
		if( item_IB )
		{
			// old calculation
			/*
			float quantity = 0;
			float wetness = 0;
			int confweight = item.ConfigGetInt("weight");
			quantity = item_IB.GetQuantity();
			wetness = item_IB.GetWet();
			
			float weight = 0;
		
			if (quantity > 0 && confweight != 0)
			{
				weight = Math.Round( (wetness + 1) * confweight * quantity );
			}
			else if (quantity > 0)
			{
				weight = Math.Round( (wetness + 1) * quantity );
			}
			else
			{
				weight=Math.Round( (wetness + 1) * confweight );
			}
			*/
			int weight = item_IB.GetItemWeight();
			
			if (root_widget.GetName() != "BackPanelWidget")
			{
				weight = item_IB.GetSingleInventoryItemWeight();
			}
			
			if (weight >= 1000)
			{
				int kilos = Math.Round(weight / 1000.0);
				WidgetTrySetText(root_widget, "ItemWeightWidget", "ABOUT " + kilos.ToString() + " KG", Colors.COLOR_DEFAULT);
			}
			else if (weight >= 500)
			{
				WidgetTrySetText(root_widget, "ItemWeightWidget", "UNDER 1 KG", Colors.COLOR_DEFAULT);
			} 
			else if (weight >= 250)
			{
				WidgetTrySetText(root_widget, "ItemWeightWidget", "UNDER 0.5 KG", Colors.COLOR_DEFAULT);
			}
			else 
			{
				WidgetTrySetText(root_widget, "ItemWeightWidget", "UNDER 0.25 KG", Colors.COLOR_DEFAULT);
			}
		}
	}
	
	//--------------------------------------------------------------------------
	static void UpdateItemInfoFoodStage(Widget root_widget, EntityAI item)
	{
		if ( item.IsInherited( Edible_Base ) && !item.IsInherited( Bottle_Base ) )
		{
			Edible_Base food_item = Edible_Base.Cast( item );
			
			ref FoodStage food_stage = food_item.GetFoodStage();
			FoodStageType food_stage_type = food_stage.GetFoodStageType();
			
			string food_stage_name = food_stage.GetFoodStageName( food_stage_type );
			food_stage_name.ToUpper();
			
			switch( food_stage_type )
			{
				case FoodStageType.RAW:
				{
					WidgetTrySetText( root_widget, "ItemFoodStageWidget", food_stage_name, Colors.COLOR_RAW );
					break;
				}
				case FoodStageType.BAKED:
				{
					WidgetTrySetText( root_widget, "ItemFoodStageWidget", food_stage_name, Colors.COLOR_BAKED );
					break;
				}
				case FoodStageType.BOILED:
				{
					WidgetTrySetText( root_widget, "ItemFoodStageWidget", food_stage_name, Colors.COLOR_BOILED );
					break;
				}
				case FoodStageType.DRIED:
				{
					WidgetTrySetText( root_widget, "ItemFoodStageWidget", food_stage_name, Colors.COLOR_DRIED );
					break;
				}
				case FoodStageType.BURNED:
				{
					WidgetTrySetText( root_widget, "ItemFoodStageWidget", food_stage_name, Colors.COLOR_BURNED );
					break;
				}
				case FoodStageType.ROTTEN:
				{
					WidgetTrySetText( root_widget, "ItemFoodStageWidget", food_stage_name, Colors.COLOR_ROTTEN );
					break;
				}
			}
		}
		else
		{
			WidgetTrySetText( root_widget, "ItemFoodStageWidget", "" );
		}
	}
	
	//--------------------------------------------------------------------------
	static void WidgetTrySetText(Widget root_widget, string widget_name, string text, int color = 0)
	{
		TextWidget widget = TextWidget.Cast( root_widget.FindAnyWidget(widget_name) );
		if (widget)
		{
			widget.SetText(text);
	
			Widget widget_background = root_widget.FindAnyWidget(widget_name+"Background");
			if (widget_background)
			{
				if (color != 0)
				{
					widget_background.Show( true );
					widget_background.SetColor(color | 0x7F000000);
				}
				else
				{
					widget_background.Show( false );
				}
			}
		}
	}

};