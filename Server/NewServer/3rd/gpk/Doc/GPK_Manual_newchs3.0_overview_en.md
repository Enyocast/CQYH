# GPK overview and SDK files from the Chinese manual

This translates sections 1–3, pages 4–6, of `GPK_Manual_newchs3.0.pdf`. Statements about capabilities, compatibility, contacts, schedules, and service levels are historical claims in that document, not independently verified current guarantees.

## 1 GPK overview

### 1.1 Functions

The manual describes GPK as a kernel-level game-protection tool with the following intended functions:

1. Guard against debuggers and hacking tools such as OllyDbg and rootkits.
2. Guard against programs that control games by simulating keyboard input.
3. Protect the game process against memory reads and writes.
4. Hash-check specified game memory regions to prevent modification.
5. Encrypt and decrypt game packets using dynamic algorithms, either directly or in addition to an algorithm designed by the game.
6. Prevent use of game speed-up tools.
7. Protect accounts against Ring 0 and Ring 3 keylogging.
8. Prevent Trojans from injecting into or modifying the game process.
9. Update the dynamic algorithm library and anti-cheat module without restarting the server, allowing a rapid response to new cheats.

### 1.2 Technical features

- **Kernel techniques:** block techniques used by cheats and Trojans and guard key system points.
- **Virtual-machine techniques:** use virtual-machine methods to increase the cost of reverse engineering without increasing system resource use, according to the manual.
- **Dynamic encryption:** use changing keys and algorithms for game packets to make reverse engineering harder.
- **Intelligent detection:** identify cheats by their distinguishing characteristics, report them to the server, and take measures according to the partner's requirements.
- **Cheat blocking:** protect key in-memory data and monitor sensitive game code against modification.

### 1.3 Claimed advantages

The manual describes anti-cheat and account-theft protection as core capabilities. It claims the design prevents offline cheats and protects against techniques used by most account-stealing Trojans. It also claims strong security, stability, modular flexibility, independent whole or partial updates without game downtime, client compatibility with Windows 2000 and later Windows versions, and compatibility with common server operating systems. It reports no compatibility problems among the users served at the time. The manual says GPK supports different business cooperation models and customized versions.

## 2 Implementation

### 2.1 Steps

1. Contact the software laboratory: Jiang Weihua, Shi Xinfeng, or `gpk@snda.com`.
2. Provide the GPK SDK to the game developer.
3. Integrate the GPK module into the game client and server according to the documentation, with technical support from the software laboratory.
4. Configure the server.
5. Test.
6. Complete the integration.

### 2.2 Schedule

The manual estimates seven to ten days, including testing but excluding server configuration.

### 2.3 Follow-up anti-cheat service

The manual says active defenses may not stop every cheat created for a particular game, so an ongoing response service is offered. It asks operators to send new cheat samples to `gpk@snda.com` with a relevant game account and, for paid cheats where possible, a cheat account. It promises a response within two hours, blocking updates for modified existing cheats within two working days, updates for entirely new cheats within four working days, and priority updates within one working day for some urgent incidents.

## 3 SDK files

The SDK supplies headers, libraries, and DLLs for integration.

### 3.1 Headers

The headers are in `include`:

- `GPKitClt.h`: client integration header.
- `GPKitSvr.h`: server integration header.

### 3.2 Libraries

The libraries are in `LIB`:

- `GPKitClt.lib`: client integration library.
- `GPKitSvr.lib`: release server integration library.
- `GPKitSvrD.lib`: debug server integration library.

## Confidentiality notice in the source

The source states that the document and SDK are Shanda property, may not be used, reworked, distributed, or transferred without Shanda's consent, and that people responsible for reviewing and safeguarding them bear legal responsibility for loss or theft.
