

function auction_search_type(owner)
    local role = Cast(owner, 'CRole');
    local user = CUserMgr:GetInstance():FindUser(role:GetSessionID());

    user:AuctionSearchType(math.random(14), math.random(7));
    
    return brvSuccess;
end

function auction_search(owner)
    local role = Cast(owner, 'CRole');

    local itemid = role:GetRandomAuctionItemID();
    if (itemid ~= 0) then
        local user = CUserMgr:GetInstance():FindUser(role:GetSessionID());
        user:AuctionSearch(0, itemid);
    end
end

function auction_query(owner)
    local role = Cast(owner, 'CRole');

    local auctionid = role:GetFirstBuyingAuction();
    if (itemid ~= 0) then
        local user = CUserMgr:GetInstance():FindUser(role:GetSessionID());
        user:AuctionQuery(auctionid);
    end
end

function auction_sell(owner)
    local role = Cast(owner, 'CRole');
    local user = CUserMgr:GetInstance():FindUser(role:GetSessionID());
    local bag = role:GetItemBag();
    
    user:GMCommand("additem 301 1");
    
    bag:Begin(CONSLOT_DEFAULT);
    local item = bag:Next(CONSLOT_DEFAULT);
    while (item) do
        if (item.m_pTemplate.m_bAuction == 1 and item.m_pTemplate.m_byCanTrade == 1 and item.m_iteminfo.m_byBindType ~= BINDTYPE_BINDED) then
            break;
        end
        item = bag:Next(CONSLOT_DEFAULT);
    end
    
    if (item) then
        user:AuctionSell(item.m_iteminfo.m_byConSlot, item.m_iteminfo.m_byItemSlot, item.m_pTemplate.m_nDefaultAuctionPrice, 0);
    end
    
    return brvSuccess;
end

function auction_cancel_sell(owner)
    local role = Cast(owner, 'CRole');

    local auctionid = role:GetFirstSellingAuction();
    if (itemid ~= 0) then
        local user = CUserMgr:GetInstance():FindUser(role:GetSessionID());
        user:AuctionCancelSell(auctionid);
    end
end

function auction_buy(owner)
end

function auction_list_my_selling(owner)
    local role = Cast(owner, 'CRole');
    local user = CUserMgr:GetInstance():FindUser(role:GetSessionID());
    
    user:AuctionListMySelling();
    
    return brvSuccess;
end

function auction_list_my_buying(owner)
    local role = Cast(owner, 'CRole');
    local user = CUserMgr:GetInstance():FindUser(role:GetSessionID());
    
    user:AuctionListMyBuying();
    
    return brvSuccess;
end

function do_auction_action(owner)
    local rand_value = math.random(8);

    if  rand_value == 1 then
        auction_search_type(owner);
    elseif rand_value == 2 then
        auction_search(owner);
    elseif rand_value == 3 then
        auction_query(owner);
    elseif rand_value == 4 then
        auction_sell(owner);
    elseif rand_value == 5 then
        auction_cancel_sell(owner);
    elseif rand_value == 6 then
        auction_buy(owner);
    elseif rand_value == 7 then
        auction_list_my_selling(owner);
    elseif rand_value == 8 then
        auction_list_my_buying(owner);
    end
end