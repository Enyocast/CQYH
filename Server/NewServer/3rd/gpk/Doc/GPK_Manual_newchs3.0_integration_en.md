# GPK client and server integration from the Chinese SDK manual

This translates the instructions and example comments in sections 4 and 5, pages 7–12, of `GPK_Manual_newchs3.0.pdf`. API names are retained. The examples in the source contain inconsistent variable names and other apparent errors; verify them against the SDK headers before using them.

## 4 Client SDK integration

1. **Start GPK.** Call `GPKStart` from the program entry point, such as `WinMain` or the MFC application constructor, before creating the game window message loop. This prevents a cheat from hooking the window before GPK starts. The call starts protection and returns an `IGPKCltDynCode` pointer. The example labels `GPKitClt.h` as the GPK header, `SGPK` as the GPK namespace, and creates the game window after the call.
2. **Set dynamic code.** After connecting to the game server and receiving dynamic-code data, call `IGPKCltDynCode::SetDynCode`. The client can use the component for encryption and decryption only after this data is set. The example describes a buffer for data received from the server, says the dynamic-code size is less than 12 KB, and labels `nlen` as the received length. It then continues with the rest of the client code.
3. **Process heartbeat data.** Pass GPK heartbeat data received from the server to `IGPKCltDynCode::ProcessAuth`, then send it back to the server. Processing overwrites the original buffer without changing its length. The example comments identify the receive buffer and length, heartbeat processing, and the send to the server.
4. **Release the component.** Call `IGPKCltDynCode::Release` when the client exits.

## 5 Server SDK integration

1. **Create the server component.** After the server program starts and before its socket service starts, call `GPKCreateSvrDynCode` to create an `IGPKSvrDynCode` component. The example labels `GPKitSvr.h` as the GPK server header and `SGPK` as the namespace.
2. **Load dynamic code.** Call `IGPKSvrDynCode::LoadBinary` with the server and client dynamic-code directories. The example labels a return of `0` or `-1` as an error.
3. **Create an authentication object for each connection.** Call `IGPKSvrDynCode::AllocAuthObject` to create an `IGPKCSAuth` object for the connected user. The example's user structure includes a pointer to that object and a comment for other game-specific fields.
4. **Send dynamic code to the client.** After `AllocAuthObject` succeeds, obtain the code through `IGPKCSAuth::GetCSAuthDynCode` and send it to the client.
5. **Send heartbeats periodically.** Set a game timer and call `IGPKCSAuth::GetAuthData` for each user every one to two minutes, sending the returned data to the client. The source says a return of `0` indicates repeated unanswered heartbeats; the game must log relevant player account information and disconnect the player. The sample's nonzero branch is labeled as sending data to the client.
6. **Check heartbeat replies.** Call `IGPKCSAuth::CheckAuthReply` after receiving a heartbeat reply. The prose says to log the player account and return value and disconnect on a result other than `CHECK_SUCCEED`. The example distinguishes `CHECK_FIND_CHEAT_NEED_KICK`, which logs and disconnects, from `CHECK_FIND_CHEAT_ONLY_LOG`, which only logs; other failures log and disconnect. This difference between prose and example should be checked against the SDK contract.
7. **Release the authentication object.** Release the `IGPKCSAuth` object when the connection session ends.
8. **Release the server component.** Call `IGPKSvrDynCode::Release` when the server exits.
9. **Reload dynamic code without restarting.** Back up the old `.bin` files and put the new paired files in their respective directories. Add a server GM command, for example `ReloadDynCode`, that calls `IGPKSvrDynCode::LoadBinary` again. The source example uses `approot\DynCodeBin\Server` and `approot\DynCodeBin\Client`; newly logged-in users then use the new dynamic-code library.
