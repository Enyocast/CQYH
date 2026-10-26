
for i = 1, 150 do
	_G["AddTitle"..i] = function (pItem, pRole)
		pRole:GetTitle():AddTitle(i);
		return 1;
	end
end
