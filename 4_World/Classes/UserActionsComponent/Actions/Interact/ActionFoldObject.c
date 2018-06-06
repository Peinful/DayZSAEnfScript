class ActionFoldObject: ActionInteractBase
{
	void ActionFoldObject()
	{
		m_MessageSuccess = "";
		m_MessageStartFail = "Hesco Box is ruined.";
		m_MessageStart = "Hesco Box is ruined.";
		m_MessageSuccess = "";
		m_MessageFail = "";
		m_MessageCancel = "";
		//m_Animation = "UNPINGRENADE";
		m_SpecialtyWeight = UASoftSkillsWeight.ROUGH_MEDIUM;
	}

	override int GetType()
	{
		return AT_FOLD_OBJECT;
	}

	override string GetText()
	{
		return "Fold the object";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		Object targetObject = target.GetObject();
		if ( targetObject.IsInherited(HescoBox) )
		{
			HescoBox hesco = HescoBox.Cast( targetObject );
			
			if ( hesco.GetState() == HescoBox.UNFOLDED )
			{
				return true;
			}
		}
		return false;
	}

	override void OnCompleteServer( PlayerBase player, ActionTarget target, ItemBase item, Param acdata )
	{
		Object targetObject = target.GetObject();
		HescoBox hesco = HescoBox.Cast( targetObject );
		if ( hesco.GetState() == HescoBox.UNFOLDED )
		{
			hesco.Fold();
		}
		
		player.GetSoftSkillManager().AddSpecialty( m_SpecialtyWeight );
	}
};