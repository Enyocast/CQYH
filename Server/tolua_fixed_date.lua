-- Loaded by the tolua++ custom build step with: toluappc.exe -L tolua_fixed_date.lua ...
--
-- tolua++ stamps every generated binding file with the time it was generated:
--     ** Generated automatically by tolua++-1.0.92 on 10/26/26 22:55:06.
-- That makes every build rewrite every generated file, so git reports hundreds of
-- modified files when nothing has really changed. Replacing date() with a constant
-- makes the output reproducible: the generated files only change when the .pkg
-- inputs change.
date = function() return "(timestamp omitted)" end
