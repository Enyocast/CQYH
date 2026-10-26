/**************************************************************************

Filename    :   AS3_VM.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/

#include "AS3_VM.h"
#include "AS3_AsString.h"
#include "AS3_VMRead.h"
#include "AS3_VTable.h"
#include "AS3_Tracer.h"

// For VM::FormatErrorMessage
#include "Kernel/SF_MsgFormat.h" 
#include "Kernel/SF_Debug.h" 

#include "Obj/AS3_Obj_Function.h"
#include "Obj/AS3_Obj_Activation.h"
#include "Obj/AS3_Obj_Catch.h"
#include "Obj/AS3_Obj_Boolean.h"
#include "Obj/AS3_Obj_Number.h"
#include "Obj/AS3_Obj_int.h"
#include "Obj/AS3_Obj_uint.h"
#include "Obj/AS3_Obj_String.h"
#include "Obj/AS3_Obj_UserDefined.h"
#include "Obj/AS3_Obj_Array.h"
#include "Obj/AS3_Obj_Namespace.h"
#include "Obj/AS3_Obj_QName.h"
#include "Obj/AS3_Obj_Error.h"
#include "Obj/Vec/AS3_Obj_Vec_Vector.h"
#include "Obj/Vec/AS3_Obj_Vec_Vector_int.h"
#include "Obj/Vec/AS3_Obj_Vec_Vector_uint.h"
#include "Obj/Vec/AS3_Obj_Vec_Vector_double.h"
#include "Obj/Vec/AS3_Obj_Vec_Vector_String.h"
#include "Obj/Vec/AS3_Obj_Vec_Vector_object.h"
#include "Obj/AS3_Obj_XML.h"
#include "Obj/AS3_Obj_XMLList.h"
#include "Obj/AS3_Obj_Global.h"
#include "Obj/AS3_Obj_EvalError.h"
#include "Obj/AS3_Obj_RangeError.h"
#include "Obj/AS3_Obj_ReferenceError.h"
#include "Obj/AS3_Obj_SecurityError.h"
#include "Obj/AS3_Obj_SyntaxError.h"
#include "Obj/AS3_Obj_TypeError.h"
#include "Obj/AS3_Obj_URIError.h"
#include "Obj/AS3_Obj_VerifyError.h"
#include "Obj/AS3_Obj_UninitializedError.h"
#include "Obj/AS3_Obj_ArgumentError.h"
#include "Obj/AS3_Obj_Global.h"
#include "Obj/Errors/AS3_Obj_Errors_MemoryError.h"

// Define SF_TRACE_FILE_LOADING if you want to trace file loading/unloading process.
// #define SF_TRACE_FILE_LOADING

namespace Scaleform { namespace GFx { namespace AS3 
{

#if defined(GFX_AS3_VERBOSE)

    static int errorMappingTable[] =
    {
        1000,
        1001,
        1002,
        1003,
        1004,
        1005,
        1006,
        1007,
        1008,
        1009,
        1010,
        1011,
        1012,
        1013,
        1014,
        1015,
        1016,
        1017,
        1018,
        1019,
        1020,
        1021,
        1022,
        1023,
        1024,
        1025,
        1026,
        1027,
        1028,
        1029,
        1030,
        1031,
        1032,
        1033,
        1034,
        1035,
        1037,
        1038,
        1039,
        1040,
        1041,
        1042,
        1043,
        1044,
        1045,
        1046,
        1047,
        1049,
        1050,
        1051,
        1052,
        1053,
        1054,
        1056,
        1057,
        1058,
        1059,
        1060,
        1061,
        1063,
        1064,
        1065,
        1066,
        1067,
        1068,
        1069,
        1070,
        1071,
        1072,
        1073,
        1074,
        1075,
        1076,
        1077,
        1078,
        1079,
        1080,
        1081,
        1082,
        1083,
        1084,
        1085,
        1086,
        1087,
        1088,
        1089,
        1090,
        1091,
        1092,
        1093,
        1094,
        1095,
        1096,
        1097,
        1098,
        1100,
        1101,
        1102,
        1103,
        1104,
        1107,
        1108,
        1109,
        1110,
        1111,
        1112,
        1113,
        1114,
        1115,
        1116,
        1117,
        1118,
        1119,
        1120,
        1121,
        1122,
        1123,
        1124,
        1125,
        1126,
        1127,
        1128,
        1500,
        1501,
        1502,
        1503,
        1504,
        1505,
        1506,
        1507,
        1508,
        1509,
        1510,

        2006,
        2007,
        2008,
        2024,
        2025,
        2030,
        2058,

        2108,
        2109,

        2136,
    };

    enum { eNumErrorConstants = sizeof(errorMappingTable) / sizeof(int) };

    static const char* errorConstants[eNumErrorConstants] =
    { 
        /* 1000,0*/ "The system is out of memory.",
        /* 1001,1*/ "The method {0} is not implemented.",
        /* 1002,2*/ "Number.toPrecision has a range of 1 to 21. Number.toFixed and Number.toExponential have a range of 0 to 20. Specified value is not within expected range.",
        /* 1003,3*/ "The radix argument must be between 2 and 36; got {0}.",
        /* 1004,4*/ "Method {0} was invoked on an incompatible object.",
        /* 1005,5*/ "Array index is not a positive integer ({0}).",
        /* 1006,6*/ "{0} is not a function.",
        /* 1007,7*/ "Instantiation attempted on a non-constructor.",
        /* 1008,8*/ "{0} is ambiguous; Found more than one matching binding.",
        /* 1009,9*/ "Cannot access a property or method of a null object reference.",
        /* 1010,10*/ "A term is undefined and has no properties.",
        /* 1011,11*/ "Method {0} contained illegal opcode {1} at offset {2}.",
        /* 1012,12*/ "The last instruction exceeded code size.",
        /* 1013,13*/ "Cannot call OP_findproperty when scopeDepth is 0.",
        /* 1014,14*/ "Class {0} could not be found.",
        /* 1015,15*/ "Method {0} cannot set default xml namespace",
        /* 1016,16*/ "Descendants operator (..) not supported on type {0}.",
        /* 1017,17*/ "Scope stack overflow occurred.",
        /* 1018,18*/ "Scope stack underflow occurred.",
        /* 1019,19*/ "Getscopeobject {0} is out of bounds.",
        /* 1020,20*/ "Code cannot fall off the end of a method.",
        /* 1021,21*/ "At least one branch target was not on a valid instruction in the method.",
        /* 1022,22*/ "Type void may only be used as a function return type.",
        /* 1023,23*/ "Stack overflow occurred.",
        /* 1024,24*/ "Stack underflow occurred.",
        /* 1025,25*/ "An invalid register {0} was accessed.",
        /* 1026,26*/ "Slot {0} exceeds slotCount={1} of {2}.",
        /* 1027,27*/ "Method_info {0} exceeds method_count={1}.",
        /* 1028,28*/ "Disp_id {0} exceeds max_disp_id={1} of {2}.",
        /* 1029,29*/ "Disp_id {0} is undefined on {1}.",
        /* 1030,30*/ "Stack depth is unbalanced. {0} != {1}.",
        /* 1031,31*/ "Scope depth is unbalanced. {0} != {1}.",
        /* 1032,32*/ "Cpool index {0} is out of range {1}.",
        /* 1033,33*/ "Cpool entry {0} is wrong type.",
        /* 1034,34*/ "Type Coercion failed: cannot convert {0} to {1}.",
        /* 1035,35*/ "Illegal super expression found in method {0}.",
        /* 1037,36*/ "Cannot assign to a method {0} on {1}.",
        /* 1038,37*/ "{0} is already defined.",
        /* 1039,38*/ "Cannot verify method until it is referenced.",
        /* 1040,39*/ "The right-hand side of instanceof must be a class or function.",
        /* 1041,40*/ "The right-hand side of operator must be a class.",
        /* 1042,41*/ "Not an ABC file.  major_version={0} minor_version={1}.",
        /* 1043,42*/ "Invalid code_length={0}.",
        /* 1044,43*/ "MethodInfo-{0} unsupported flags={1}.",
        /* 1045,44*/ "Unsupported traits kind={0}.",
        /* 1046,45*/ "MethodInfo-{0} referenced before definition.",
        /* 1047,46*/ "No entry point was found.",
        /* 1049,47*/ "Prototype objects must be vanilla Objects.",
        /* 1050,48*/ "Cannot convert {0} to primitive.",
        /* 1051,49*/ "Illegal early binding access to {0}.",
        /* 1052,50*/ "Invalid URI passed to {0} function.",
        /* 1053,51*/ "Illegal override of {0} in {1}.",
        /* 1054,52*/ "Illegal range or target offsets in exception handler.",
        /* 1056,53*/ "Cannot create property {0} on {1}.",
        /* 1057,54*/ "{0} can only contain methods.",
        /* 1058,55*/ "Illegal operand type: {0} must be {1}.",
        /* 1059,56*/ "ClassInfo-{0} is referenced before definition.",
        /* 1060,57*/ "ClassInfo {0} exceeds class_count={1}.",
        /* 1061,58*/ "The value {0} cannot be converted to {1} without losing precision.",
        /* 1063,59*/ "Argument count mismatch on {0}. Expected from {1} to {2}, got {3}.",
        /* 1064,60*/ "Cannot call method {0} as constructor.",
        /* 1065,61*/ "Variable {0} is not defined.",
        /* 1066,62*/ "The form function('function body') is not supported.",
        /* 1067,63*/ "Native method {0} has illegal method body.",
        /* 1068,64*/ "{0} and {1} cannot be reconciled.",
        /* 1069,65*/ "Property {0} not found on {1} and there is no default value.",
        /* 1070,66*/ "Method {0} not found on {1}",
        /* 1071,67*/ "Function {0} has already been bound to {1}.",
        /* 1072,68*/ "Disp_id 0 is illegal.",
        /* 1073,69*/ "Non-override method {0} replaced because of duplicate disp_id {1}.",
        /* 1074,70*/ "Illegal write to read-only property {0} on {1}.",
        /* 1075,71*/ "Math is not a function.",
        /* 1076,72*/ "Math is not a constructor.",
        /* 1077,73*/ "Illegal read of write-only property {0} on {1}.",
        /* 1078,74*/ "Illegal opcode/multiname combination: {0}<{1}>.",
        /* 1079,75*/ "Native methods are not allowed in loaded code.",
        /* 1080,76*/ "Illegal value for namespace.",
        /* 1081,77*/ "Property {0} not found on {1} and there is no default value.",
        /* 1082,78*/ "No default namespace has been set.",
        /* 1083,79*/ "The prefix \"{0}\" for element \"{1}\" is not bound.",
        /* 1084,80*/ "Element or attribute (\"{0}\") does not match QName production: QName::=(NCName':')?NCName.",
        /* 1085,81*/ "The element type \"{0}\" must be terminated by the matching end-tag \"</{1}>\".",
        /* 1086,82*/ "The {0} method only works on lists containing one item.",
        /* 1087,83*/ "Assignment to indexed XML is not allowed.",
        /* 1088,84*/ "The markup in the document following the root element must be well-formed.",
        /* 1089,85*/ "Assignment to lists with more than one item is not supported.",
        /* 1090,86*/ "XML parser failure: element is malformed.",
        /* 1091,87*/ "XML parser failure: Unterminated CDATA section.",
        /* 1092,88*/ "XML parser failure: Unterminated XML declaration.",
        /* 1093,89*/ "XML parser failure: Unterminated DOCTYPE declaration.",
        /* 1094,90*/ "XML parser failure: Unterminated comment.",
        /* 1095,91*/ "XML parser failure: Unterminated attribute.",
        /* 1096,92*/ "XML parser failure: Unterminated element.",
        /* 1097,93*/ "XML parser failure: Unterminated processing instruction.",
        /* 1098,94*/ "Illegal prefix {0} for no namespace.",
        /* 1100,95*/ "Cannot supply flags when constructing one RegExp from another.",
        /* 1101,96*/ "Cannot verify method {0} with unknown scope.",
        /* 1102,97*/ "Illegal default value for type {0}.",
        /* 1103,98*/ "Class {0} cannot extend final base class.",
        /* 1104,99*/ "Attribute \"{0}\" was already specified for element \"{1}\".",
        /* 1107,100*/ "The ABC data is corrupt, attempt to read out of bounds.",
        /* 1108,101*/ "The OP_newclass opcode was used with the incorrect base class.",
        /* 1109,102*/ "Attempt to directly call unbound function {0} from method {1}.",
        /* 1110,103*/ "{0} cannot extend {1}.",
        /* 1111,104*/ "{0} cannot implement {1}.",
        /* 1112,105*/ "Argument count mismatch on class coercion.  Expected 1, got {0}.",
        /* 1113,106*/ "OP_newactivation used in method without NEED_ACTIVATION flag.",
        /* 1114,107*/ "OP_getglobalslot or OP_setglobalslot used with no global scope.",
        /* 1115,108*/ "{0} is not a constructor.",
        /* 1116,109*/ "second argument to Function.prototype.apply must be an array.",
        /* 1117,110*/ "Invalid XML name: {0}.",
        /* 1118,111*/ "Illegal cyclical loop between nodes.",
        /* 1119,112*/ "Delete operator is not supported with operand of type {0}.",
        /* 1120,113*/ "Cannot delete property {0} on {1}.",
        /* 1121,114*/ "Method {0} has a duplicate method body.",
        /* 1122,115*/ "Interface method {0} has illegal method body.",
        /* 1123,116*/ "Filter operator not supported on type {0}.",
        /* 1124,117*/ "OP_hasnext2 requires object and index to be distinct registers.",
        /* 1125,118*/ "The index {0} is out of range {1}.",
        /* 1126,119*/ "Cannot change the length of a fixed Vector.",
        /* 1127,120*/ "Type application attempted on a non-parameterized type.",
        /* 1128,121*/ "Incorrect number of type parameters for {0}. Expected {1}, got {2}.",
        /* 1500,122*/ "Error occurred opening file {0}.",
        /* 1501,123*/ "Error occurred writing to file {0}.",
        /* 1502,124*/ "A script has executed for longer than the default timeout period of 15 seconds.",
        /* 1503,125*/ "A script failed to exit after 30 seconds and was terminated.",
        /* 1504,126*/ "End of file.",
        /* 1505,127*/ "The string index {0} is out of bounds; must be in range {1} to {2}.",
        /* 1506,128*/ "The specified range is invalid.",
        /* 1507,129*/ "Argument {0} cannot be null.",
        /* 1508,130*/ "The value specified for argument {0} is invalid.",
        /* 1509,131*/ "There was an error decompressing the data.",
        /* 1510,132*/ "When the callback argument is a method of a class, the optional this argument must be null.",

        /* 2006,133*/ "The supplied index is out of bounds.",
        /* 2007,134*/ "Parameter {0} must be non-null.",
        /* 2008,135*/ "Parameter {0} must be one of the accepted values.",
        /* 2024,136*/ "An object cannot be added as a child of itself.",
        /* 2025,137*/ "The supplied {0} must be a child of the caller.",
        /* 2030,138*/ "End of file was encountered.",
        /* 2058,139*/ "There was an error decompressing the data.",

        /* 2108,140*/ "Scene {0} was not found.",
        /* 2109,141*/ "Frame label {0} was not found in scene {1}.",

        /* 2136,142*/ "The SWF file {0} contains invalid data.",
    };

    const char* GetErrorMsg(const int ind)
    {
        // Do binary search.
        int min = 0;
        int max = eNumErrorConstants - 1;

        while (min <= max)
        {
            const int mid = (min + max) >> 1;
            const int curValue = errorMappingTable[mid];

            if (curValue == ind) 
            {
                min = mid;
                break;
            } 
			else if (ind < curValue) 
                max = mid - 1;
            else 
                min = mid + 1;
        }

        int ident = errorMappingTable[min];

        if (ident == ind)
        {
			int index = min;
            return errorConstants[index];
        }

        return NULL;
    }
#endif


///////////////////////////////////////////////////////////////////////////

// ***** VMAbcFile Implementation

VMAbcFile::VMAbcFile(VM& vm, const Ptr<Abc::File>& file)
    : GASRefCountBase(&vm.GetGC()), VMRef(vm), File(file)
{
    SetHasFinalize();
    SF_ASSERT(File.GetPtr() != NULL);

    // String with index zero is empty.
    IntStrings.PushBack(vm.GetStringManager().GetEmptyStringNode());

    // We HAVE TO resize OpCodeArray and Exceptions here because we need to use
    // reference to an element. (It will be invalidated during resizing of Array)
    const UPInt size = file->GetMethodBodyTable().GetSize();
    OpCodeArray.Resize(size);
    Exceptions.Resize(size);

    vm.AddVMAbcFileWeak(this);
}

VMAbcFile::~VMAbcFile()
{
    SF_DEBUG_MESSAGE2(GFX_UNLOAD_TRACE_ENABLED, "~VMAbcFile %s %p\n", File->GetName().ToCStr(), this);
    GetVM().RemoveVMAbcFileWeak(this);
}

void VMAbcFile::Finalize_GC()
{
    SF_DEBUG_MESSAGE2(GFX_UNLOAD_TRACE_ENABLED, "VMAbcFile::Finalize %s %p\n", 
        File->GetName().ToCStr(), this);
    UnRegister();
}

void VMAbcFile::ForEachChild_GC(Collector* prcc, GcOp op) const
{
    UPInt i = 0;
    UPInt size = 0;

    IntNamespaces.ForEachChild_GC(prcc, op SF_DEBUG_ARG(*this));

#ifdef SF_AS3_ENABLE_GETABSOBJECT
    // AbsObjects
    {
        HashSetLH<SPtr<GASRefCountBase> >::ConstIterator it = AbsObjects.Begin();
        for (; !it.IsEnd(); ++it)
            AS3::ForEachChild_GC<GASRefCountBase, Mem_Stat>(prcc, *it, op SF_DEBUG_ARG(*this));
    }
#endif

    // IntNamespaceSets
    {
        size = IntNamespaceSets.GetSize();
        for (i = 0; i < size; ++i)
            AS3::ForEachChild_GC<NamespaceSet, Mem_Stat>(prcc, IntNamespaceSets[i], op SF_DEBUG_ARG(*this));
    }

    // GlobalObjects
    {
        HashSetLH<SPtr<Instances::GlobalObjectScript> >::ConstIterator it = GlobalObjects.Begin();
        for (; !it.IsEnd(); ++it)
            AS3::ForEachChild_GC<Instances::GlobalObjectScript, Mem_Stat>(prcc, *it, op SF_DEBUG_ARG(*this));
    }

    // Children
    {
        size = Children.GetSize();
        for (i = 0; i < size; ++i)
            AS3::ForEachChild_GC<VMAbcFile, Mem_Stat>(prcc, Children[i], op SF_DEBUG_ARG(*this));
    }

    // ActivationTraitsCache
    {
        TActivationTraitsCache::ConstIterator it = ActivationTraitsCache.Begin();
        while (!it.IsEnd())
        {
            AS3::ForEachChild_GC<InstanceTraits::Activation, Mem_Stat>(prcc, it->Second, op SF_DEBUG_ARG(*this));
            ++it;
        }
    }

    // FunctionTraitsCache
    {
        TFunctionTraitsCache::ConstIterator it = FunctionTraitsCache.Begin();
        while (!it.IsEnd())
        {
            AS3::ForEachChild_GC<InstanceTraits::Function, Mem_Stat>(prcc, it->Second, op SF_DEBUG_ARG(*this));
            ++it;
        }
    }

    // LoadedClasses
    {
        size = LoadedClasses.GetSize();
        for (UPInt i = 0; i < size; ++i)
            AS3::ForEachChild_GC<ClassTraits::Traits, Mem_Stat>(prcc, LoadedClasses[i], op SF_DEBUG_ARG(*this));
    }
}

bool VMAbcFile::RegisterUserDefinedClassTraits()
{
    const Abc::ClassTable& classes = GetClasses();
    UPInt numOfClasses = 0;
    VM& vm = GetVM();

#ifdef SF_TRACE_FILE_LOADING
    FlashUI& ui = vm.GetUI();
#endif

    // Filter out scripts, which
    // 1) initialize classes, which are not registered;
    // 2) duplicate identical scripts from other files.

    // Register uninitialized traits,
    for (UPInt i = 0; i < classes.GetSize(); ++i)
    {
        const Abc::ClassInfo& class_info = classes.Get(i);
        const Abc::Multiname& name = class_info.GetName(GetConstPool());
        const ASString str_name = GetInternedString(name.GetNameInd());
        const Instances::Namespace& ns = GetInternedNamespace(name.GetNamespaceInd());

        // check for *scaleform extension* packages.
        if (IsScaleformGFx(ns))
            // Skip it.
            continue;

        const ClassTraits::Traits* ctr = vm.Resolve2ClassTraits(str_name, ns);
        if (ctr == NULL)
        {
            // Class is not registered yet.
            Pickable<ClassTraits::Traits> ud(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) ClassTraits::UserDefined(*this, vm, class_info));
            vm.ClassTraitsSet.Add(str_name, ns, VM::TClassTraitsCache::ValueType(ud.GetPtr()));
            ++numOfClasses;
            LoadedClasses.PushBack(ud);

#ifdef SF_TRACE_FILE_LOADING
            ui.Output(FlashUI::Output_Action, "Registering class ");
            if (!ns.GetUri().IsEmpty())
            {
                ui.Output(FlashUI::Output_Action, ns.GetUri().ToCStr());
                ui.Output(FlashUI::Output_Action, "::");
            }
            ui.Output(FlashUI::Output_Action, str_name.ToCStr());
            ui.Output(FlashUI::Output_Action, "\n");
#endif
        }
        else
		{
            // This class is already loaded from another file. Skip it.
#ifdef SF_TRACE_FILE_LOADING
            ui.Output(FlashUI::Output_Action, "Class ");
            if (!ns.GetUri().IsEmpty())
            {
                ui.Output(FlashUI::Output_Action, ns.GetUri().ToCStr());
                ui.Output(FlashUI::Output_Action, "::");
            }
            ui.Output(FlashUI::Output_Action, str_name.ToCStr());
            ui.Output(FlashUI::Output_Action, " is already registered with another file (");
            ui.Output(FlashUI::Output_Action, ctr->GetFilePtr()->GetAbcFile().GetName().ToCStr());
            ui.Output(FlashUI::Output_Action, ").\n");
#endif

            // Add file, which defines this class to the list of children.
            VMAbcFile* file = ctr->GetFilePtr();
            if (file)
            {
                bool alreadyDependsOn = false;
                const UPInt jsize = Children.GetSize();
                for (UPInt j = 0; j < jsize; ++j)
                {
                    if (Children[j].GetPtr() == file)
                    {
                        alreadyDependsOn = true;
                        break;
                    }
                }

                if (!alreadyDependsOn)
                    Children.PushBack(file);
            }
		}
    }

    if (numOfClasses == 0 && classes.GetSize() != 0)
        return false;

    bool uninitialize = false;

    // Initialize uninitialized traits,
    for (UPInt i = 0; i < classes.GetSize(); ++i)
    {
        const Abc::ClassInfo& class_info = classes.Get(i);
        const Abc::Multiname& name = class_info.GetName(GetConstPool());
        const ASString str_name = GetInternedString(name.GetNameInd());
        const Instances::Namespace& ns = GetInternedNamespace(name.GetNamespaceInd());

        if (IsScaleformGFx(ns))
            // Skip it.
            continue;

        /* Another way of doing the same thing.
        const ClassTraits::UserDefined* ud = static_cast<const ClassTraits::UserDefined*>(Resolve2ClassTraits(str_name, ns));

        // Filter out classes, which are defined in other files. This happens.
        if (ud && (&ud->GetFile() == &file))
            ud->Initialize();
        */

        ClassTraits::UserDefined& ud = vm.GetUserDefinedTraits(*this, class_info);

        // Filter out classes, which are defined in other files. This happens.
        if (&ud.GetFile() != this)
		{
#ifdef SF_TRACE_FILE_LOADING
            ui.Output(FlashUI::Output_Action, "Class ");
            if (!ns.GetUri().IsEmpty())
            {
                ui.Output(FlashUI::Output_Action, ns.GetUri().ToCStr());
                ui.Output(FlashUI::Output_Action, "::");
            }
            ui.Output(FlashUI::Output_Action, str_name.ToCStr());
            ui.Output(FlashUI::Output_Action, " is already registered with another file.\n");
#endif
            continue;
		}

        // Initialize() can throw exceptions.
        if (!ud.Initialize())
        {
            if (vm.IsException())
                vm.OutputAndIgnoreException();

            // Delete ClassTraits.
            vm.ClassTraitsSet.Remove(str_name, ns);
            --numOfClasses;
            uninitialize = true;
            break;
        }
    }

    // UnRegister whole file.
    if (uninitialize)
    {
        // Remove traits, which may be not completely initialized because of an exception,
        UnregisterUserDefinedClassTraits();
        return false;
    }

    return (classes.GetSize() == 0 || (classes.GetSize() != 0 && numOfClasses != 0));
}

bool VMAbcFile::RegisterScrips(bool to_execute)
{
    VM& vm = GetVM();

    // Register scripts.
    const Abc::File& file = GetAbcFile();
    const UPInt n = file.GetScripts().GetSize();
    for (UPInt i = 0; i < n; ++i)
    {
        const Abc::ScriptInfo& script = file.GetScripts().Get(i);

        SPtr<InstanceTraits::GlobalObjectScript> it;

        // Can throw exceptions.
        it.Pick(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_ITraits_Mem) InstanceTraits::GlobalObjectScript(
            *this,
            vm, 
            script
            ));

        if (vm.IsException())
            return false;

        SPtr<Instances::GlobalObjectScript> inst = it->MakeInstance();

        if (vm.IsException())
            return false;

        vm.GlobalObjects.PushBack(inst.GetPtr());

        // Register this global object with its file.
        GlobalObjects.Set(inst);

        inst->InitUserDefinedClassTraits();
    }

    // Execute last script if necessary.
    if (to_execute && n > 0)
        vm.GlobalObjects.Back()->Execute();

    return !vm.IsException();
}

void VMAbcFile::UnregisterUserDefinedClassTraits()
{
#ifdef SF_TRACE_FILE_LOADING
    VM& vm = GetVM();
    FlashUI& ui = vm.GetUI();
    ui.Output(FlashUI::Output_Action, "\nFile ");
    ui.Output(FlashUI::Output_Action, File->GetSource().ToCStr());
    ui.Output(FlashUI::Output_Action, " will be completely unregistered.\n");
#endif

    const UPInt size = LoadedClasses.GetSize();
    for (UPInt i = 0; i < size; ++i)
    {
        ClassTraits::Traits& ctr = *LoadedClasses[i];

        if (ctr.IsValid())
        {
            // Fast way.
            InstanceTraits::Traits& itr = ctr.GetInstanceTraits();
            const ASString& str_name = itr.GetNameRef();
            const Instances::Namespace& ns = itr.GetNamespace();

#ifdef SF_TRACE_FILE_LOADING
            ui.Output(FlashUI::Output_Action, "Unregistering class ");
            if (!ns.GetUri().IsEmpty())
            {
                ui.Output(FlashUI::Output_Action, ns.GetUri().ToCStr());
                ui.Output(FlashUI::Output_Action, "::");
            }
            ui.Output(FlashUI::Output_Action, str_name.ToCStr());
            ui.Output(FlashUI::Output_Action, "\n");
#endif

            GetVM().ClassTraitsSet.Remove(str_name, ns);
        }
        else
        {
            // Slow way.
            GetVM().ClassTraitsSet.RemoveValue(&ctr);
        }
    }
    LoadedClasses.Clear();
}

CheckResult VMAbcFile::Load(bool to_execute)
{
#ifdef SF_TRACE_FILE_LOADING
    FlashUI& ui = GetVM().GetUI();
    ui.Output(FlashUI::Output_Action, "\nRegistering file: ");
    ui.Output(FlashUI::Output_Action, File->GetSource().ToCStr());
    ui.Output(FlashUI::Output_Action, "\n");
#endif

    // Register class traits.
    // Register scripts.
    return RegisterUserDefinedClassTraits() && RegisterScrips(to_execute);
}

void VMAbcFile::UnRegister()
{
    if (!GetVM().RemoveVMAbcFileWeak(this))
        return; // already unregistered

    // Get rid of class traits.
    UnregisterUserDefinedClassTraits();

    // Destroy generated opcode because it holds pointers to objects.
    const UPInt size = OpCodeArray.GetSize();
    for (UPInt i = 0; i < size; ++i)
        OpCodeArray[i].Clear();

    // !!! DO NOT clear  OpCodeArray because it can be used again.
    OpCodeArray.Clear();

#ifdef SF_AS3_ENABLE_GETABSOBJECT
    // Clear AbsObjects because there is no optimized opcode any more.
    AbsObjects.Clear();
#endif

    // Get rid of Global Objects.
    HashSetLH<SPtr<Instances::GlobalObjectScript> >::Iterator it = GlobalObjects.Begin();
    for (; !it.IsEnd(); ++it)
    {
        Object* o_ptr = *it;
        const UPInt vm_size = VMRef.GlobalObjects.GetSize();

        for (UPInt j = 0; j < vm_size; ++j)
        {
            Instances::GlobalObject* v = VMRef.GlobalObjects[j];
            if (v == o_ptr)
            {
                VMRef.GlobalObjects.RemoveAt(j);
                break;
            }
        }
    }
    GlobalObjects.Clear();

    // Clear the rest.
    
    // LoadedClasses is cleared by UnregisterUserDefinedClassTraits().
    // ??? Children should not be cleared.
    Children.Clear();
    IntNamespaces.Clear();
    IntNamespaceSets.Clear();
    IntStrings.Clear();
    ActivationTraitsCache.Clear();
    FunctionTraitsCache.Clear();
    Exceptions.Clear();
}

Instances::Namespace& VMAbcFile::GetInternedNamespace(const Abc::Multiname& mn)
{
    SPtr<Instances::Namespace>* pNs = IntNamespaces.Get(mn);

    if (pNs == NULL)
    {
        const Abc::ConstPool& cp = GetAbcFile().GetConstPool();
        const Abc::NamespaceInfo& info = mn.GetNamespace(cp);
        const StringDataPtr& uri = info.GetNameURI();
        ASString URI = GetVM().GetStringManager().CreateString(uri.ToCStr(), uri.GetSize());

        if (mn.GetNextMultinameIndex() >= 0)
        {
            const Abc::Multiname& next_mn = mn.GetNextMultiname(cp);
            const Abc::NamespaceInfo& next_info = next_mn.GetNamespace(cp);
            const StringDataPtr& next_uri = next_info.GetNameURI();

            URI += "$";
            URI += GetVM().GetStringManager().CreateString(next_uri.ToCStr(), next_uri.GetSize());
        }

        Pickable<Instances::Namespace> ns_ptr = GetVM().MakeInternedNamespace(info.GetKind(), URI);

        IntNamespaces.Add(mn, ns_ptr);
        pNs = IntNamespaces.Get(mn);
    }

    return **pNs;
}

Instances::Namespace& VMAbcFile::GetInternedNamespace(UPInt nsIndex)
{
    SPtr<Instances::Namespace>* pNs = IntNamespaces.Get(nsIndex);

    if (pNs == NULL)
    {
        const Abc::NamespaceInfo& info = GetAbcFile().GetConstPool().GetNamespace(nsIndex);
        Pickable<Instances::Namespace> ns_ptr = GetVM().MakeInternedNamespace(info.GetKind(), info.GetNameURI());

        IntNamespaces.Add(nsIndex, ns_ptr);
        pNs = IntNamespaces.Get(nsIndex);
    }

    return **pNs;
}

NamespaceSet& VMAbcFile::GetInternedNamespaceSet(UPInt nsSetIndex)
{    
    if (nsSetIndex >= IntNamespaceSets.GetSize())
        IntNamespaceSets.Resize(nsSetIndex + 1);
    
    // Initialize.
    if (!IntNamespaceSets[nsSetIndex])
    {
        Pickable<NamespaceSet> nss(SF_HEAP_NEW_ID(GetVM().GetMemoryHeap(), StatMV_VM_VMAbcFile_Mem) NamespaceSet(VMRef));
        IntNamespaceSets[nsSetIndex] = nss;
        const Abc::NamespaceSetInfo& info = GetAbcFile().GetConstPool().GetNamespaceSet(nsSetIndex);
        
        // Fill it up with data.
        const UInt8* ptr = info.GetData();
        UInt32 size;
        UInt32 ns_ind;

        Abc::Read(ptr, size);
        for(UInt32 i = 0; i < size; ++i)
        {
            Abc::Read(ptr, ns_ind);
            nss->Add(GetInternedNamespace(ns_ind));
        }
    }
    
    return *IntNamespaceSets[nsSetIndex];
}

ASString VMAbcFile::GetInternedString(UPInt strIndex)
{
    if (strIndex >= IntStrings.GetSize())
        IntStrings.Resize(strIndex + 1);

    if (IntStrings[strIndex].GetPtr() == NULL)
    {
        const StringDataPtr& str = GetAbcFile().GetConstPool().GetString(AbsoluteIndex(strIndex));
        IntStrings[strIndex].SetPtr(GetVM().GetStringManager().CreateString(
            str.ToCStr(), str.GetSize()
            ).GetNode());
    }

    return ASString(IntStrings[strIndex]);
}

const Abc::TOpCode& VMAbcFile::GetOpCode(SInt32 mbi_ind, const CallFrame& cf)
{
    SF_ASSERT(mbi_ind >= 0 && static_cast<UPInt>(mbi_ind) < OpCodeArray.GetSize());

    if (OpCodeArray[mbi_ind].GetSize() == 0)
    {
        VM& vm = GetVM();
        Tracer tracer(vm.GetMemoryHeap(), cf, OpCodeArray[mbi_ind], Exceptions[mbi_ind]);

        if (!vm.IsException())
            tracer.EmitCode();
    }

    return OpCodeArray[mbi_ind];
}

Value VMAbcFile::GetDetailValue(const Abc::ValueDetail& d)
{
    const int value_ind = d.GetIndex();

    // If we have a value ...
    if (value_ind > 0)
    {
        switch(d.GetKind())
        {
        case Abc::CONSTANT_Int:
            return Value(GetConstPool().GetInt(value_ind));
        case Abc::CONSTANT_UInt:
            return Value(GetConstPool().GetUInt(value_ind));
        case Abc::CONSTANT_Double:
            return Value(MakeValueNumber(GetConstPool().GetDouble(value_ind)));
        case Abc::CONSTANT_Utf8:
            {
                const StringDataPtr& str = GetConstPool().GetString(AbsoluteIndex(value_ind));
                return Value(
                    GetVM().GetStringManager().CreateString(
                    str.ToCStr(), str.GetSize()
                    ));
            }
        case Abc::CONSTANT_True:
            return Value(true);
        case Abc::CONSTANT_False:
            return Value(false);
        case Abc::CONSTANT_Null:
            return Value::GetNull();
        case Abc::CONSTANT_Undefined:
            return Value::GetUndefined();
        case Abc::CONSTANT_Namespace:
        case Abc::CONSTANT_PackageNamespace:
        case Abc::CONSTANT_PackageInternalNs:
        case Abc::CONSTANT_ProtectedNamespace:
        case Abc::CONSTANT_ExplicitNamespace:
        case Abc::CONSTANT_StaticProtectedNs:
        case Abc::CONSTANT_PrivateNs:
            return Value(&GetInternedNamespace(d.GetIndex()));
        default:
            SF_ASSERT(false);
            break;
        }
    }

    return Value::GetUndefined();
}

InstanceTraits::Activation& 
VMAbcFile::GetActivationInstanceTraits(const Abc::MethodBodyInfo& mbi SF_DEBUG_ARG(const ASString& name))
{
    VM& vm = GetVM();

    if (mbi.GetTraitsCount())
    {
        TActivationTraitsCache::ValueType* ptr = ActivationTraitsCache.Get(&mbi);

        if (ptr == NULL)
        {
            Pickable<InstanceTraits::Activation> t(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_ITraits_Mem) InstanceTraits::Activation(*this, vm, mbi SF_DEBUG_ARG(name)));
            ActivationTraitsCache.Add(&mbi, t);

            return *t;
        }

        return **ptr;
    }

    return *vm.NoActivationTraits;
}

InstanceTraits::Function&
VMAbcFile::GetFunctionInstanceTraits(UInt32 method_ind)
{
    VM& vm = GetVM();
    const Abc::MethodBodyInfo& mbi = GetMethodBodyInfo(method_ind);
    if (mbi.GetTraitsCount())
    {
        TFunctionTraitsCache::ValueType* ptr = FunctionTraitsCache.Get(&mbi);

        if (ptr == NULL)
        {
            Pickable<InstanceTraits::Function> t(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_ITraits_Mem) InstanceTraits::Function(this, vm, FunctionCI, mbi));

            if (vm.IsException())
                return *vm.NoFunctionTraits;

            FunctionTraitsCache.Add(&mbi, t);

            return *t;
        }

        return **ptr;
    }

    return *vm.NoFunctionTraits;
}


///////////////////////////////////////////////////////////////////////////
// Original isdigit() may assert if c > 127.
inline bool IsDigit(char c)
{
    return ('0' <= c && c <= '9');
}

///////////////////////////////////////////////////////////////////////////
CheckResult GetArrayInd(ASStringNode* sn, UInt32& ind)
{
    const unsigned ssize = sn->Size;

    if (ssize > 0)
    {
        const char* sdata = sn->pData;
        char c = sdata[0];

        if (c == '0')
        {
            ind = 0;
            return ssize == 1;
        }

        if (IsDigit(c))
        {
            for (unsigned i = 1; i < ssize; ++i)
            {
                if (!IsDigit(sdata[i]))
                    return false;
            }

            char* end;
            Value::Number num = strtod(sdata, &end);

            if (num <= SF_MAX_UINT32)
            {
                ind = (UInt32)num;
                return true;
            }
        } 
    }

    return false;
}

///////////////////////////////////////////////////////////////////////////
CheckResult GetArrayInd(const Multiname& prop_name, UInt32& ind)
{
    bool result = false;
    const Value& name = prop_name.GetName();

    if (name.IsString())
        result = GetArrayInd(name.GetStringNode(), ind);
    else if (name.IsNumeric())
        result = name.Convert2UInt32(ind);

    return result;
}

///////////////////////////////////////////////////////////////////////////
CheckResult GetVectorInd(ASStringNode* sn, UInt32& ind)
{
    bool result = false;

    Value::Number num;
    if (GetStrNumber(sn, num))
    {
        if (num <= SF_MAX_UINT32)
        {
            ind = (UInt32)num;
            result = true;
        }
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////
CheckResult GetVectorInd(const Multiname& prop_name, UInt32& ind)
{
    bool result = false;
    const Value& name = prop_name.GetName();

    /* Old version, which is copied over from GetArrayInd().
    if (name.IsString())
        result = GetArrayInd(name.GetStringNode(), ind);
    else if (name.IsNumeric())
        result = name.Convert2UInt32(ind);
    */

    switch (name.GetKind())
    {
    case Value::kString:
        result = GetVectorInd(name.GetStringNode(), ind);
        break;
    case Value::kUInt:
        ind = name.AsUInt();
        result = true;
        break;
    case Value::kInt:
        if (name.AsInt() >= 0)
        {
            ind = static_cast<UInt32>(name.AsInt());
            result = true;
        }
        break;
    case Value::kNumber:
        {
            Value::Number n;
            const Value::Number num = name.AsNumber();

            if (num >= 0 && ::modf(num, &n) == 0.0 && num <= SF_MAX_UINT32)
            {
                ind = static_cast<UInt32>(num);
                result = true;
            }
        }
        break;
    default:
        break;
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////
CheckResult GetStrNumber(ASStringNode* sn, Value::Number& result)
{
    if (sn == NULL)
        return false;

    const unsigned ssize = sn->Size;

    if (ssize > 0)
    {
        const char* sdata = sn->pData;
        char c = sdata[0];
        if (IsDigit(c))
        {
            for (unsigned i = 1; i < ssize; ++i)
            {
                c = sdata[i];
                if (!IsDigit(c))
                {
                    if (c == '.')
                    {
                        for (unsigned j = i + 1; j < ssize; ++j)
                        {
                            if (sdata[j] != '0')
                                return false;
                        }

                        // Everything is fine.
                        break;
                    }

                    return false;
                }
            }

            char* end;
            result = strtod(sdata, &end);

            return true;
        } 
    }

    return false;
}

///////////////////////////////////////////////////////////////////////////
CallFrame::CallFrame(MemoryHeap* heap)
: DiscardResult(false)
#ifndef SF_AS3_ENABLE_CALLFRAME_CACHE
, ACopy(false)
#endif
SF_DEBUG_ARG(RegisteredFunction(false))
, ScopeStackBaseInd(0)
, CP(0)
, pRegisterFile(NULL)
, pHeap(heap)
, pFile(NULL)
, MBIIndex(0)
, pSavedScope(NULL)
, OriginationTraits(NULL)
, pScopeStack(NULL)
, PrevInitialStackPos(NULL)
SF_DEBUG_ARG(PrevFirstStackPos(NULL))
SF_DEBUG_ARG(PrevReservedNum(0))
SF_DEBUG_ARG(CurrFileInd(0))
SF_DEBUG_ARG(CurrLineNumber(0))
SF_DEBUG_ARG(StartTicks(0))
{
    // VM is not available at this time.
    // SF_ASSERT(GetVM().OpStack.IsValid());
}

#ifdef SF_AS3_ENABLE_CALLFRAME_CACHE

CallFrame::~CallFrame()
{
    SF_ASSERT(GetVM().OpStack.IsValid());
}

#else

CallFrame::CallFrame(const CallFrame& other)
: DiscardResult(other.DiscardResult)
, ACopy(true)
SF_DEBUG_ARG(RegisteredFunction(other.RegisteredFunction))
, ScopeStackBaseInd(other.ScopeStackBaseInd)
, CP(other.CP)
, pRegisterFile(other.pRegisterFile)
, pHeap(other.pHeap)
, pFile(other.pFile)
, MBIIndex(other.MBIIndex)
, pSavedScope(other.pSavedScope)
, OriginationTraits(other.OriginationTraits)
, pScopeStack(other.pScopeStack)
, PrevInitialStackPos(other.PrevInitialStackPos)
SF_DEBUG_ARG(PrevFirstStackPos(other.PrevFirstStackPos))
SF_DEBUG_ARG(PrevReservedNum(other.PrevReservedNum))
SF_DEBUG_ARG(Name(other.Name))
SF_DEBUG_ARG(CurrFileInd(0))
SF_DEBUG_ARG(CurrLineNumber(0))
SF_DEBUG_ARG(StartTicks(other.StartTicks))
, Invoker(other.Invoker)
{
    // VM is not available at this time.
    // SF_ASSERT(GetVM().OpStack.IsValid());
}

CallFrame::~CallFrame()
{
    if (pRegisterFile && pScopeStack && ACopy)
    {
        VM::OpStackType& stack = GetVM().OpStack;
        stack.ReleaseReserved(SF_DEBUG_CODE(PrevReservedNum) SF_DEBUG_ARG(PrevFirstStackPos));
        pRegisterFile->ReleaseReserved(static_cast<UInt16>(GetMethodBodyInfo().GetMaxLocalRegisterIndex()));
        ClearScopeStack();

        SF_ASSERT(stack.IsValid());
    }
}

CallFrame& CallFrame::operator =(const CallFrame& other)
{
    if (this != &other)
    {
        DiscardResult = other.DiscardResult;
        ACopy = true;
        SF_DEBUG_CODE(RegisteredFunction = other.RegisteredFunction;)
        ScopeStackBaseInd = other.ScopeStackBaseInd;
        CP = other.CP;
        pRegisterFile = other.pRegisterFile;
        pHeap = other.pHeap;
        pFile = other.pFile;
        MBIIndex = other.MBIIndex;
        pSavedScope = other.pSavedScope;
        OriginationTraits = other.OriginationTraits;
        pScopeStack = other.pScopeStack;
        PrevInitialStackPos = other.PrevInitialStackPos;
        SF_DEBUG_CODE(PrevFirstStackPos = other.PrevFirstStackPos;)
        SF_DEBUG_CODE(PrevReservedNum = other.PrevReservedNum;)
        SF_DEBUG_CODE(Name = other.Name;)
        SF_DEBUG_CODE(CurrFileInd = other.CurrFileInd;)
        SF_DEBUG_CODE(CurrLineNumber = other.CurrLineNumber;)
        SF_DEBUG_CODE(StartTicks = other.StartTicks;)
        Invoker = other.Invoker;
    }

    SF_ASSERT(GetVM().OpStack.IsValid());

    return *this;
}
#endif

Abc::TOpCodeVTP CallFrame::GetCP() const
{
    if (CP == NULL)
        CP = GetCode().GetDataPtr();

    return CP;
}

void CallFrame::SetupRegisters(const Abc::MethodInfo& mi, const Value& _this, unsigned argc, const Value* argv)
{
    // Register 0 holds the "this" object. This value is never null.
    int reg = 0;
    SetRegister(reg++, (_this.IsNullOrUndefined() ? GetVM().GetGlobalObject() : _this));
    
    const UPInt param_count = mi.GetParamCount();
    const UPInt first_opt_param_num = param_count - mi.GetOptionalParamCount();
    
    // Registers 1 through method_info.param_count holds parameter values coerced to the declared types
    // of the parameters. If fewer than method_body_info.local_count values are supplied to the call then
    // the remaining values are either the values provided by default value declarations (optional arguments)
    // or the value undefined.
    
    for(unsigned i = 0; i < param_count; ++i)
    {
        // Coerce to the argument's type ...

        // Resolve multiname ...
        const Abc::Multiname& mn = mi.GetParamType(GetFile().GetConstPool(), i);
        const ClassTraits::Traits* to = GetVM().Resolve2ClassTraits(GetFile(), mn);

        if (to == NULL)
        {
            return GetVM().ThrowReferenceError(VM::Error(VM::eClassNotFoundError, GetVM()
                SF_DEBUG_ARG(mn.GetName(GetFile().GetConstPool()).ToCStr())
                ));
        }

        Value result = Value::GetUndefined();

        if (i < argc)
        {
#if 0
            // This simplified version breaks "as3/Definitions/Classes/Override/ExtDefaultOverRidePublic.abc"
            // This is the only problem so far.

            // TBD: Replace runtime coerce with Trace-time coerce.
            SetRegister(reg++, argv[i]);
#else
            if (!to->Coerce(argv[i], result))
            {
                // A TypeError is thrown if value cannot be coerced to the specified type.
                return GetVM().ThrowTypeError(VM::Error(VM::eCheckTypeFailedError, GetVM()
                    SF_DEBUG_ARG(argv[i])
                    SF_DEBUG_ARG(to->GetName().ToCStr())
                    ));
            }
#endif
        } else
        {
            // No more arguments from stack ...
            if(mi.HasOptionalParams() && i >= first_opt_param_num)
            {
                if (!to->Coerce(GetFile().GetDetailValue(mi.GetOptionalParam(i - first_opt_param_num)), result))
                {
                    // A TypeError is thrown if value cannot be coerced to the specified type.
                    return GetVM().ThrowTypeError(VM::Error(VM::eCheckTypeFailedError, GetVM()
                        SF_DEBUG_ARG(GetFile().GetDetailValue(mi.GetOptionalParam(i - first_opt_param_num)))
                        SF_DEBUG_ARG(to->GetName().ToCStr())
                        ));
                }
            }
#ifndef SF_AS3_ENABLE_ARGNUM_VALIDATION_IN_TRACER
            else if (to != &GetVM().GetClassTraitsClassClass())
            {
                return GetVM().ThrowArgumentError(VM::Error(VM::eWrongArgumentCountError, GetVM()
                    SF_DEBUG_ARG(Name->pData)
                    SF_DEBUG_ARG(static_cast<int>(first_opt_param_num))
                    SF_DEBUG_ARG(static_cast<int>(param_count))
                    SF_DEBUG_ARG(argc)
                    ));
            }
#endif
        }

        // Store value ...
        SetRegister(reg++, result);
    }

    if (mi.NeedRest())
    {
        // If NEED_REST is set in method_info.flags, the method_info.param_count+1 register is set up to
        // reference an array that holds the superfluous arguments.

        Pickable<Instances::Array> arr = GetVM().MakeArray();
        // Store arr ASAP to prevent problems with GC in case of exception.
        SetRegister(reg++, arr);

        if (argc > param_count)
            arr->Append((unsigned)(argc - param_count), argv + param_count);
    } else if (mi.NeedArguments())
    {
        // If NEED_ARGUMENTS is set in method_info.flags, the method_info.param_count+1 register is set up
        // to reference an "arguments" object that holds all the actual arguments: see ECMA-262 for more
        // information. (The AVM2 is not strictly compatible with ECMA-262; it creates an Array object for
        // the "arguments" object, whereas ECMA-262 requires a plain Object.)

        // "arguments" is a regular Array. There is no an explicit "arguments" class.
        Pickable<Instances::Array> arr = GetVM().MakeArray();
        // Store arr ASAP to prevent problems with GC in case of exception.
        SetRegister(reg++, arr);

        // Two registers are taken by "this" and "array of arguments".
        // Everything in between can be copied into arr.
        const unsigned avail_regn = reg - 2;

        // Populate arr with data.
        for (unsigned i = 0; i < argc; ++i)
        {
            if (i < avail_regn)
                arr->PushBack(GetRegister(i + 1));
            else
                // We have more arguments than declared types.
                arr->PushBack(argv[i]);
        }

        // Add property "callee".
        {
            Value callee;

            Value::KindType vk = Invoker.GetKind();
            switch (vk)
            {
            case Value::kVTableInd:
                SF_ASSERT(_this.GetObject());
                // Make a MethodIndClosure.
                callee = Value(_this.GetObject(), Invoker.GetVTableInd());
                break;
            case Value::kFunction:
#if 0
                // DO NOT delete code below.
                // Code below is not correct.
                // We shouldn't create a MethodClosure for a Function.
                // Make a method closure by storing "this".
                callee = GetVM().GetClassFunction().MakeInstance2(Invoker, _this);
#else
                callee = Invoker;
#endif
                break;
            default:
                callee = Invoker;
            }

            arr->AddDynamicSlotValuePair(
                GetVM().GetStringManager().CreateConstString("callee"), 
                callee
                );
        }
    }
}

void CallFrame::ClearOpStack()
{
    VM::OpStackType& stack = GetVM().OpStack;
    stack.PopReserved(PrevInitialStackPos);
}

#ifdef SF_AS3_ENABLE_CALLFRAME_CACHE

void CallFrame::Clear()
{
    SF_ASSERT(pRegisterFile);
    SF_ASSERT(pScopeStack);

    Invoker.SetUndefined();
    VM::OpStackType& stack = GetVM().OpStack;
    stack.ReleaseReserved(SF_DEBUG_CODE(PrevReservedNum) SF_DEBUG_ARG(PrevFirstStackPos));
    const Abc::MethodBodyInfo& mbi = GetMethodBodyInfo();
    pRegisterFile->ReleaseReserved(static_cast<UInt16>(mbi.GetMaxLocalRegisterIndex()));
    ClearScopeStack();
}

///////////////////////////////////////////////////////////////////////////
CallFrameCache::CallFrameCache(MemoryHeap* heap) : Heap(heap), CallFrames(heap) 
{
}

CallFrameCache::~CallFrameCache()
{
    const UPInt size = CallFrames.GetSize();
    for (UPInt i = 0; i < size; ++i)
        delete CallFrames[i];
}

CallFrame* CallFrameCache::MakeCallFrame()
{
    CallFrame* result = NULL;
    if (CallFrames.IsEmpty())
        result = SF_HEAP_NEW(Heap) CallFrame(Heap);
    else
    {
        result = CallFrames.Back();
        CallFrames.PopBack();
    }

    return result;
}

void CallFrameCache::DestroyCallFrame(CallFrame* cf)
{
    SF_ASSERT(cf);
    cf->Clear();
    CallFrames.PushBack(cf);
}

#endif

///////////////////////////////////////////////////////////////////////////
VM::VM(FlashUI& _ui, FileLoader& loader, StringManager& sm, ASRefCountCollector& gc)
: Initialized(false)
, InDestructor(false)
, StringManagerRef(sm)
, GC(gc)
, UI(_ui)
, Loader(loader)
, InInitializer(0)
, MHeap(Memory::GetHeapByAddress(&GetSelf()))
#ifdef SF_AS3_ENABLE_CALLFRAME_CACHE
, CFCache(GetMemoryHeap())
#endif
, CallStack(GetMemoryHeap())
, ScopeStack(GetMemoryHeap())
, HandleException(false)
, GlobalObjects()

#ifdef SF_AMP_SERVER
, ActiveLineTimestamp(0)
#endif

, PublicNamespace(MakePickable(SF_HEAP_NEW_ID(GetMemoryHeap(), StatMV_VM_Instance_Mem) Instances::Namespace(GetSelf(), Abc::NS_Public, "")))
, AS3Namespace(MakePickable(SF_HEAP_NEW_ID(GetMemoryHeap(), StatMV_VM_Instance_Mem) Instances::Namespace(GetSelf(), Abc::NS_Public, NS_AS3)))
, VectorNamespace(MakePickable(SF_HEAP_NEW_ID(GetMemoryHeap(), StatMV_VM_Instance_Mem) Instances::Namespace(GetSelf(), Abc::NS_Public, NS_Vector)))

, TraitsClassClass(PrepareClassTraits(SF_HEAP_NEW_ID(GetMemoryHeap(), StatMV_VM_CTraits_Mem) ClassTraits::ClassClass(GetSelf())))
, TraitsObject(PrepareClassTraits(SF_HEAP_NEW_ID(GetMemoryHeap(), StatMV_VM_CTraits_Mem) ClassTraits::Object(GetSelf())))
, TraitsNamespace(PrepareClassTraits(SF_HEAP_NEW_ID(GetMemoryHeap(), StatMV_VM_CTraits_Mem) ClassTraits::Namespace(GetSelf())))
, TraitsFunction(PrepareClassTraits(SF_HEAP_NEW_ID(GetMemoryHeap(), StatMV_VM_CTraits_Mem) ClassTraits::Function(GetSelf(), FunctionCI)))
, TraitsBoolean(PrepareClassTraits(SF_HEAP_NEW_ID(GetMemoryHeap(), StatMV_VM_CTraits_Mem) ClassTraits::Boolean(GetSelf())))
, TraitsNumber(PrepareClassTraits(SF_HEAP_NEW_ID(GetMemoryHeap(), StatMV_VM_CTraits_Mem) ClassTraits::Number(GetSelf())))
, TraitsInt(PrepareClassTraits(SF_HEAP_NEW_ID(GetMemoryHeap(), StatMV_VM_CTraits_Mem) ClassTraits::int_(GetSelf())))
, TraitsUint(PrepareClassTraits(SF_HEAP_NEW_ID(GetMemoryHeap(), StatMV_VM_CTraits_Mem) ClassTraits::uint(GetSelf())))
, TraitsString(PrepareClassTraits(SF_HEAP_NEW_ID(GetMemoryHeap(), StatMV_VM_CTraits_Mem) ClassTraits::String(GetSelf())))
, TraitsArray(PrepareClassTraits(SF_HEAP_NEW_ID(GetMemoryHeap(), StatMV_VM_CTraits_Mem) ClassTraits::Array(GetSelf())))
, TraitsCatch(PrepareClassTraits(SF_HEAP_NEW_ID(GetMemoryHeap(), StatMV_VM_CTraits_Mem) ClassTraits::Catch(GetSelf())))
, TraitsVector(PrepareClassTraits(SF_HEAP_NEW_ID(GetMemoryHeap(), StatMV_VM_CTraits_Mem) ClassTraits::Vector(GetSelf())))
, TraitsVector_int(PrepareClassTraits(SF_HEAP_NEW_ID(GetMemoryHeap(), StatMV_VM_CTraits_Mem) ClassTraits::Vector_int(GetSelf())))
, TraitsVector_uint(PrepareClassTraits(SF_HEAP_NEW_ID(GetMemoryHeap(), StatMV_VM_CTraits_Mem) ClassTraits::Vector_uint(GetSelf())))
, TraitsVector_Number(PrepareClassTraits(SF_HEAP_NEW_ID(GetMemoryHeap(), StatMV_VM_CTraits_Mem) ClassTraits::Vector_double(GetSelf())))
, TraitsVector_String(PrepareClassTraits(SF_HEAP_NEW_ID(GetMemoryHeap(), StatMV_VM_CTraits_Mem) ClassTraits::Vector_String(GetSelf())))

#ifdef SF_ENABLE_XML
, TraitsQName(PrepareClassTraits(SF_HEAP_NEW_ID(GetMemoryHeap(), StatMV_VM_CTraits_Mem) ClassTraits::QName(GetSelf())))
, TraitsXML(PrepareClassTraits(SF_HEAP_NEW_ID(GetMemoryHeap(), StatMV_VM_CTraits_Mem) ClassTraits::XML(GetSelf())))
, TraitsXMLList(PrepareClassTraits(SF_HEAP_NEW_ID(GetMemoryHeap(), StatMV_VM_CTraits_Mem) ClassTraits::XMLList(GetSelf())))
#endif

, TraitsNull(MakePickable(SF_HEAP_NEW_ID(GetMemoryHeap(), StatMV_VM_ITraits_Mem) InstanceTraits::Anonimous(GetSelf())))
, TraitsVoid(MakePickable(SF_HEAP_NEW_ID(GetMemoryHeap(), StatMV_VM_ITraits_Mem) InstanceTraits::Void(GetSelf())))

, NoFunctionTraits(MakePickable(SF_HEAP_NEW_ID(GetMemoryHeap(), StatMV_VM_ITraits_Mem) InstanceTraits::Function(GetSelf(), FunctionCICpp)))

, NoActivationTraits(MakePickable(SF_HEAP_NEW_ID(GetMemoryHeap(), StatMV_VM_ITraits_Mem) InstanceTraits::Activation(GetSelf())))

, TraitaGlobalObject(MakePickable(SF_HEAP_NEW_ID(GetMemoryHeap(), StatMV_VM_ITraits_Mem) InstanceTraits::GlobalObject(GetSelf())))
, GlobalObject(MakePickable(new(Memory::AllocInHeap(GetMemoryHeap(), sizeof(Instances::GlobalObjectCPP))) Instances::GlobalObjectCPP(GetSelf(), *TraitaGlobalObject)))
, GlobalObjectValue(GlobalObject)
{
    NoFunctionTraits->SetConstructor(Pickable<Class>(&GetClassFunction(), PickValue));

    Initialized = true;

    GlobalObjects.PushBack(GlobalObject.GetPtr());

    const UPInt n = Loader.GetSize();
    for (UPInt i = 0; i < n; ++i)
    {
        const Ptr<Abc::File>& file = Loader.GetFile(i);

        // Execute the last one.
        LoadFile(file, i == (n - 1));
    }

    // Delayed initialization to prevent circular dependencies.
    {
        // Set up traits of the public namespace, which was created uninitialized.
        // !!! For some reason that causes memory leaks.
        //PublicNamespace->pTraits = &ClassNamespace->GetInstanceTraits();
        //AS3Namespace->pTraits = &ClassNamespace->GetInstanceTraits();

        // ClassClass delayed initialization.
        {
            // ClassClass is a child of Object (like everything else).
            TraitsClassClass->SetParentTraits(TraitsObject.GetPtr());

            TraitsClassClass->RegisterSlots();

            // Prototype of ClassClass cannot be set in constructor because
            // ClassObject is not initialized at this time.
            GetClassClass().SetupPrototype();
        }

        TraitsObject->RegisterSlots();
        TraitsNamespace->RegisterSlots();
    }

#ifndef SF_AS3_CLASS_AS_SLOT
    Instances::Namespace& ns = GetPublicNamespace();
    ClassTraits::Traits* ctr;

    ctr = TraitsObject;
    ClassTraitsSet.Add(ctr->GetName(), ns, ctr);

    ctr = TraitsClassClass;
    ClassTraitsSet.Add(ctr->GetName(), ns, ctr);

    ctr = TraitsNamespace;
    ClassTraitsSet.Add(ctr->GetName(), ns, ctr);

    ctr = TraitsFunction;
    ClassTraitsSet.Add(ctr->GetName(), ns, ctr);

    ctr = TraitsBoolean;
    ClassTraitsSet.Add(ctr->GetName(), ns, ctr);

    ctr = TraitsNumber;
    ClassTraitsSet.Add(ctr->GetName(), ns, ctr);

    ctr = TraitsInt;
    ClassTraitsSet.Add(ctr->GetName(), ns, ctr);

    ctr = TraitsUint;
    ClassTraitsSet.Add(ctr->GetName(), ns, ctr);

    ctr = TraitsString;
    ClassTraitsSet.Add(ctr->GetName(), ns, ctr);

    ctr = TraitsArray;
    ClassTraitsSet.Add(ctr->GetName(), ns, ctr);

#ifdef SF_ENABLE_XML
    ctr = TraitsQName;
    ClassTraitsSet.Add(ctr->GetName(), ns, ctr);

    ctr = TraitsXML;
    ClassTraitsSet.Add(ctr->GetName(), ns, ctr);

    ctr = TraitsXMLList;
    ClassTraitsSet.Add(ctr->GetName(), ns, ctr);
#endif
#endif
}

VM::~VM()
{
    InDestructor = true;

    // This situation should be handled by the garbage col  lector.
    // Because of dependencies.
    //ClassClass->ReleasePrototype();
    UnregisterAllAbcFiles();
}

void VM::UnregisterAllAbcFiles()
{
    bool oi = InDestructor;
    InDestructor = true;
    for (UPInt i = 0, n = VMAbcFilesWeak.GetSize(); i < n; ++i)
    {
        VMAbcFilesWeak[i]->UnRegister();
    }
    VMAbcFilesWeak.Clear();
    InDestructor = oi;
}

SPtr<VMAbcFile> VM::FindVMAbcFileWeak(const char* name) const 
{
    for (UPInt i = 0, n = VMAbcFilesWeak.GetSize(); i < n; ++i)
    {
        if (VMAbcFilesWeak[i]->GetAbcFile().GetName() == name)
        {
            return SPtr<VMAbcFile>(VMAbcFilesWeak[i]);
        }
    }
    return SPtr<VMAbcFile>(NULL);
}

void VM::AddVMAbcFileWeak(VMAbcFile* f)
{
    if (!InDestructor)
    {
        VMAbcFilesWeak.PushBack(f);
    }
}

bool VM::RemoveVMAbcFileWeak(VMAbcFile* f)
{
    if (!InDestructor)
    {
        for (UPInt i = 0, n = VMAbcFilesWeak.GetSize(); i < n; ++i)
        {
            if (VMAbcFilesWeak[i] == f)
            {
                VMAbcFilesWeak.RemoveAt(i);
                return true;
            }
        }
    }
    return false;
}

UPInt VM::GetAllLoadedAbcFiles(Scaleform::Array<SPtr<VMAbcFile> >* destArray) const
{
    UPInt i = 0;
    if (!InDestructor)
    {
        for (UPInt n = VMAbcFilesWeak.GetSize(); i < n; ++i)
        {
            destArray->PushBack(VMAbcFilesWeak[i]);
        }
    }
    return i;    
}

void VM::RegisterClassTraits(ClassTraits::Traits& tr)
{
    const InstanceTraits::Traits& itr = tr.GetInstanceTraits();

    RegisterClassTraits(itr.GetName(), itr.GetNamespace(), tr);
}

bool IsScaleformGFx(const Instances::Namespace& ns)
{
    static const StringDataPtr scaleform_gfx("scaleform.gfx");
    const ASString& uri = ns.GetUri();
    const StringDataPtr str(uri.ToCStr(), uri.GetSize());

    return (str.GetSize() >= scaleform_gfx.GetSize() && SFstrncmp(str.ToCStr(), scaleform_gfx.ToCStr(), scaleform_gfx.GetSize()) == 0);
}

void VM::RegisterClassTraitsVector(ClassTraits::Traits& tr)
{
    const Instances::Namespace& ns = GetInternedNamespace(Abc::NS_Public, NS_Vector);

    RegisterClassTraits(tr.GetInstanceTraits().GetClass().GetName(), ns, tr);
}

Pickable<Instances::Object> VM::MakeObject() const
{
    InstanceTraits::Object& itr = static_cast<InstanceTraits::Object&>(GetClassTraitsObject().GetInstanceTraits());
    return itr.MakeInstance(itr);
}

Pickable<Instances::Array> VM::MakeArray() const
{
    InstanceTraits::Array& itr = static_cast<InstanceTraits::Array&>(GetClassTraitsArray().GetInstanceTraits());
    return itr.MakeInstance(itr);
}

ASString VM::AsString(const Value& value)
{
    StringManager& sm = GetStringManager();
    ASString result = sm.CreateEmptyString();

    if (!value.Convert2String(result))
    {
        // Exception.
        // Do nothing about it.
        ;
    }
    
    return result;
}

const ClassTraits::Traits* VM::GetRegisteredClassTraits(const Multiname& mn)
{
    const ClassTraits::Traits* result = NULL;

    // Both branches seem to work fine.
    // First branch seems to result in better performance.
#if 1
    if (mn.IsAnyType())
        // Code below worked fine.
        // But using GetClassTraitsObject() in Resolve2ClassTraits() causes several dozen of tests to fail.
        //result = &GetClassTraitsObject();
        result = &GetClassTraitsClassClass();
    else
    {
        ClassTraits::Traits** pptraits = ClassTraitsSet.Get(mn);
        result = pptraits ? *pptraits : NULL;
    }
#else
    ClassTraits::Traits** pptraits = ClassTraitsSet.Get(mn);
    result = pptraits ? *pptraits : NULL;
#endif

    return result;
}

const ClassTraits::Traits* VM::Resolve2ClassTraits(const ASString& name, const Instances::Namespace& ns)
{
    const ClassTraits::Traits* result = GetRegisteredClassTraits(name, ns);

    if (result == NULL)
    {
        ClassTraits::Traits* r = GetGlobalObjectCPP().GetClassTraits(name, ns);
        result = r;

        if (result)
            ClassTraitsSet.Add(name, ns, r);
    }

    return result;
}

const ClassTraits::Traits* VM::Resolve2ClassTraits(const Multiname& mn)
{
    const ClassTraits::Traits* result = GetRegisteredClassTraits(mn);

    if (result == NULL)
    {
        StringManager& sm = GetStringManager();
        ASString name = sm.CreateEmptyString();

        if (!mn.GetName().Convert2String(name))
            // Error
            return result;

        ClassTraits::Traits* r = GetGlobalObjectCPP().GetClassTraits(name, mn.GetNamespace());
        result = r;

        if (result)
            ClassTraitsSet.Add(name, mn.GetNamespace(), r);
    }

    return result;
}

const ClassTraits::Traits* VM::Resolve2ClassTraits(VMAbcFile& file, const Abc::Multiname& mn)
{
    if (&mn == &file.GetConstPool().GetAnyType())
    {
        // !!! ATTENSION !!!
        // This is a fundamental problem.
        // The major difference between Class and Object is that Class leaves
        // *undefined* unchanged, in opposite, Object will convert *undefined*
        // to *null*.

        // Object can represent any type.
        // Using code below will cause several dozen of tests to fail.
        //return &GetClassTraitsObject();
        return &GetClassTraitsClassClass();
    }

    const ASString name = file.GetInternedString(mn.GetNameInd());

    if (name == GetStringManager().GetBuiltin(AS3Builtin_void))
        // Should this be Object?
        return &GetClassTraitsObject();

    SF_ASSERT(mn.IsQName());
    const Instances::Namespace& ns = file.GetInternedNamespace(mn.GetNamespaceInd());
    const ClassTraits::Traits* ctr = Resolve2ClassTraits(name, ns);

    // Handle Vector<>.
    if (ctr == &GetClassTraitsVector())
    {
        const ClassTraits::Traits* elem_ctr = NULL;

        if (mn.GetNextMultinameIndex() == 0)
            elem_ctr = &GetClassTraitsObject();
        else
        {
            const Abc::Multiname& next = mn.GetNextMultiname(file.GetConstPool());
            elem_ctr = Resolve2ClassTraits(file, next);
        }

        if (elem_ctr)
        {
            if (elem_ctr == &GetClassTraitsInt())
                ctr = &GetClassTraitsVectorSInt();
            else if (elem_ctr == &GetClassTraitsUInt())
                ctr = &GetClassTraitsVectorUInt();
            else if (elem_ctr == &GetClassTraitsNumber())
                ctr = &GetClassTraitsVectorNumber();
            else if (elem_ctr == &GetClassTraitsString())
                ctr = &GetClassTraitsVectorString();
            //else
            // Condition below should be removed at some point. 
            else if (elem_ctr->IsValid())
            {
                const ClassTraits::Traits& vctr = static_cast<const Classes::Vector&>(ctr->GetInstanceTraits().GetClass()).Resolve2Vector(*elem_ctr);

                ctr = &vctr;
            }
        }
    }

    return ctr;
}

bool VM::IsOfType(const Value& v, const char* type_name)
{
    const Multiname mn(*this, type_name);

    const ClassTraits::Traits* ctr = Resolve2ClassTraits(mn);
    return (ctr && IsOfType(v, *ctr));
}

inline
Value::Number GetFractionalPortion(Value::Number v)
{
    double r; // We cannot use Value::Number here. 

    return modf(v, &r);
}

bool VM::IsOfType(const Value& v, const ClassTraits::Traits& ctr) const
{
    const BuiltinTraitsType tt = ctr.GetTraitsType();
    const Value::KindType k = v.GetKind();

    switch (k)
    {
    case Value::kUndefined:
        return false;
    case Value::kBoolean:
        // Boolean is final.
        return tt == Traits_Boolean || IsObject(ctr);
    case Value::kInt:
        if (tt == Traits_UInt)
            return v.AsInt() >= 0; // It is not correct to use SF_MIN_UINT32 here.
        else if (tt == Traits_Number)
            return true;

        // int is final.
        return tt == Traits_SInt || IsObject(ctr);
    case Value::kUInt:
        if (tt == Traits_SInt)
            return v.AsUInt() <= SF_MAX_SINT32;
        else if (tt == Traits_Number)
            return true;

        // uint is final.
        return tt == Traits_UInt || IsObject(ctr);
    case Value::kNumber:
        {
            double r; // We cannot use Value::Number here.

            if (modf(v.AsNumber(), &r) == 0)
            {
                if (tt == Traits_UInt)
                    return r >= SF_MIN_UINT32 && r <= SF_MAX_UINT32;
                else if (tt == Traits_SInt)
                    return r >= SF_MIN_SINT32 && r <= SF_MAX_SINT32;
            }
        }

        // Number is final.
        return tt == Traits_Number || IsObject(ctr);
    case Value::kString:
        if (v.GetStringNode())
            // String is final.
            return tt == Traits_String || IsObject(ctr);
        else
            return false;

    case Value::kObject:
        if (v.GetObject() == NULL)
            return false;
        // fall through.    
    case Value::kFunction:
    case Value::kNamespace:
    case Value::kThunkFunction:        
    case Value::kThunkClosure:        
    case Value::kVTableIndClosure:        
        return GetClassTraits(v).IsOfType(ctr);

    case Value::kClass:
        if (v.GetObject() == NULL)
            return false;
        return v.GetObject()->GetTraits().GetClass().GetClassTraits().IsOfType(ctr);

    default:
        SF_ASSERT(false);
        break;
    }

    return false;
}

int VM::OnException(Abc::TCodeOffset offset, CallFrame& cf)
{
    int position = -1;
    const Abc::MethodBodyInfo::Exception& e = cf.GetException();
    UPInt handler_num = 0;

    while (e.FindExceptionInfo(offset, handler_num))
    {
        const Abc::MethodBodyInfo::ExceptionInfo& ei = e.Get(handler_num);
        const int et_ind = ei.GetExceptionTypeInd();
        
        if (et_ind == 0)
        {
            // This handler can handle any type of exceptions ...
            
            // The value and scope stacks in the handling method are cleared before the handler is entered.
            // If a handler is found then the stack is cleared, the exception object is pushed onto the stack.
            cf.ClearOpStack();
            OpStack.PushBack(ExceptionObj);
            // Clean *exception* value ...
            ExceptionObj.Clean();
            cf.ClearScopeStack();
            
            position = ei.GetTargetPos();
            break;
        } else
        {
            // Undefined ExceptionObj should be ignored.
            if (!ExceptionObj.IsUndefined())
            {
                //const String& en = GetConstPool().GetString(Abc::StringID(et_ind));
                const ClassTraits::Traits& exc_ctr = GetClassTraits(ExceptionObj);

                HandleException = false;
                const ClassTraits::Traits* handler_tr = Resolve2ClassTraits(cf.GetFile(), cf.GetFile().GetConstPool().GetMultiname(et_ind));
                if (IsException())
                {
                    ; // Oops. Exception during exception handling.
                }
                HandleException = true;

                if (handler_tr && exc_ctr.IsOfType(*handler_tr))
                {
                    // This handler can handle this type of exceptions ...

                    // The value and scope stacks in the handling method are cleared before the handler is entered.
                    // If a handler is found then the stack is cleared, the exception object is pushed onto the stack.
                    cf.ClearOpStack();
                    OpStack.PushBack(ExceptionObj);
                    // Clean *exception* value ...
                    ExceptionObj.Clean();
                    cf.ClearScopeStack();

                    position = ei.GetTargetPos();
                    break;
                }
            }
        }

        ++handler_num;
    }
    
    HandleException = (position < 0);
        
    return position;
}

void VM::exec_getsuper(VMAbcFile& file, UInt32 v) 
{

    ReadMnObjectRef args(file, v);

    if (IsException())
        return;

    // MA: eReadSealedError or eWriteOplyError possible in property
    const Value value(args.ArgObject, PickValue);
    if (!GetSuperProperty(*this, GetCurrCallFrame().GetOriginationTraits(), args.ArgObject, value, args.ArgMN))
        return ThrowReferenceError(VM::Error(VM::eIllegalSuperCallError, *this
            SF_DEBUG_ARG(args.ArgMN.GetName())
            ));
}

void VM::exec_setsuper(VMAbcFile& file, UInt32 index) 
{
    ReadValueMnObject args(file, index);
    
    if (IsException())
        return;

    // Semantic of this operation is not very clear to me ...
    // Let's do it this way ...
    
    if (!SetSuperProperty(*this, GetCurrCallFrame().GetOriginationTraits(), args.ArgObject, args.ArgMN, args.ArgValue))
        return ThrowReferenceError(VM::Error(VM::eIllegalSuperCallError, *this
            SF_DEBUG_ARG(args.ArgMN.GetName())
            ));
}

void VM::exec_setproperty(VMAbcFile& file, UInt32 mn_index) 
{
    // Set a property.
    
    // Read arguments ...
    ReadValueMnObject args(file, mn_index);
    
    if (IsException())
        return;
    
    SetProperty(*this, args.ArgObject, args.ArgMN, args.ArgValue).DoNotCheck();
}

void VM::exec_callproperty(VMAbcFile& file, UInt32 mn_index, UInt32 arg_count)
{
    // Call a property.
    
    // Read arguments ...
    ReadArgsMnObject args(file, arg_count, mn_index);
    
    if (IsException())
        return;
    
    // Resolve property ...
    PropRef prop;

    FindObjProperty(prop, *this, args.ArgObject, args.ArgMN);
    
    if (prop)
    {
        Value func;
        
        if (!prop.GetSlotValueUnsafe(*this, func, SlotInfo::valExecute))
            return;
        
        // A TypeError is thrown if the property specified by the
        // multiname is null or undefined.
        if (func.IsNullOrUndefined())
        {
            return ThrowTypeError(VM::Error(VM::eCallOfNonFunctionError, *this
                SF_DEBUG_ARG(args.ArgMN.GetName())
                ));
        }
        
        // The [[Call]] property is invoked on the value of the resolved property with the arguments 
        // obj, arg1, ..., argn. 
        Execute(func, args.ArgObject, arg_count, args.GetCallArgs());
    } 
    else
    {
        // No property ...
        if (GetValueTraits(args.ArgObject).IsDynamic())
        {
            // In case of a dynamic object property might be created.
            // But we do not create it for the time being. We just throw
            // an exception.
            ThrowTypeError(VM::Error(VM::eCallOfNonFunctionError, *this
                SF_DEBUG_ARG(args.ArgMN.GetName())
                ));
            return;
        }
        else
        {
            return ThrowReferenceError(VM::Error(VM::ePropertyNotFoundError, *this
                    SF_DEBUG_ARG(args.ArgMN.GetName())
                    SF_DEBUG_ARG(args.ArgObject)
                    ));
        }
    }
}

void VM::exec_returnvoid()
{
    // Return from a method.

    // Return from the currently executing method. This returns the value undefined. If the
    // method has a return type, then undefined is coerced to that type and then returned.

    /* DO NOT delete this code. It was original behavior.
    OpStack.PushBack(Value::GetUndefined());
    */
    if (!GetCurrCallFrame().NeedToDiscardResult())
        OpStack.PushBack(Value::GetUndefined());

    /* DO NOT delete this code !!!
    Commented out because of a performance reason.
    There was no problem with this so far.
    if (!GetCurrCallFrame().NeedToDiscardResult())
    // Can throw exceptions.
    Coerce2ReturnType(OpStack.Back(), OpStack.Back());
    */
}

void VM::exec_returnvalue()
{
    // Return a value from a method.

    // return_value is popped off of the stack, and coerced to the expected return type of the
    // method. The coerced value is what is actually returned from the method.

    // It is returned on stack, so, if we do not want to coerce it (for the time being), we can
    // just leave it there.

    // A TypeError is thrown if return_value cannot be coerced to the expected return type of the
    // executing method.

    /* DO NOT delete this code. It was original behavior.
    // Coerce to the argument's type ...
    // This "if" statements is a little bit tricky.
    if (!GetCurrCallFrame().NeedToDiscardResult())
    // Can throw exceptions.
    Coerce2ReturnType(OpStack.Back(), OpStack.Back());
    */

    if (GetCurrCallFrame().NeedToDiscardResult())
    {
	    // Below is the old code.
//         if (OpStack.Back().IsPrimitive())
//             // Primitive value cannot be cast to an object, so, just get rid of it.
//             OpStack.Pop();
//         else
//         {
//             // Can throw exceptions.
//             Coerce2ReturnType(OpStack.Back(), OpStack.Back());
//             if (IsException())
//                 return;
// 
//             if (OpStack.GetSize() > 1)
//             {
//                 Value v = OpStack.Pop();
//                 OpStack.Pop();
//                 OpStack.PushBack(v);
//             }
//         }

	/* Commenting out code below will result in a memory leak with the /Tamarin/acceptance/ecma3/ExecutionContexts/e10_1_6.abc test

        {
            if (OpStack.GetSize() > 0)
            {
		// Can throw exceptions.
		Coerce2ReturnType(OpStack.Back(), OpStack.Back());
		if (IsException())
                    return;

		if (OpStack.GetSize() > 1)
		{
			UPInt size = OpStack.GetSize();

			Alg::Swap(OpStack[size - 1], OpStack[size - 2]);
			OpStack.PopBack();
		}
            }
        }
	*/

        OpStack.PopBack();
    }
    else
        Coerce2ReturnType(OpStack.Top0(), OpStack.Top0());
}

void VM::exec_callproplex(VMAbcFile& file, UInt32 mn_index, UInt32 arg_count)
{
    // Call a property.
    
    // Read arguments ...
    ReadArgsMnObject args(file, arg_count, mn_index);
    
    if (IsException())
        return;
    
    // The property specified by the multiname at index is resolved on the object obj. The [[Call]]
    // property is invoked on the value of the resolved property with the arguments null, arg1, ...,
    // argn. The result of the call is pushed onto the stack.
    
    // Resolve a property ...
    
    PropRef prop;

    FindObjProperty(prop, *this, args.ArgObject, args.ArgMN);

    if (prop)
    {
        Value func;
        
        if (!prop.GetSlotValueUnsafe(*this, func, SlotInfo::valExecute))
            return;
        
        // A TypeError is thrown if the property specified by the
        // multiname is null or undefined.
        if (func.IsNullOrUndefined())
        {
            ThrowTypeError(VM::Error(VM::eCallOfNonFunctionError, *this
                SF_DEBUG_ARG(args.ArgMN.GetName())
                ));
            return;
        }

        // The [[Call]]
        // property is invoked on the value of the resolved property with the arguments null, arg1, ...,
        // argn. The result of the call is pushed onto the stack.

        // This is the only difference from *callproperty* I could find so far ...
        Execute(func, Value::GetUndefined(), arg_count, args.GetCallArgs());
    }
    else
    {
        // No property ...
        if (GetValueTraits(args.ArgObject).IsDynamic())
        {
            // In case of a dynamic object property might be created.
            // But we do not create it for the time being. We just throw
            // an exception.
            ThrowTypeError(VM::Error(VM::eCallOfNonFunctionError, *this
                SF_DEBUG_ARG(args.ArgMN.GetName())
                ));
            return;
        }
        else
        {
            return ThrowReferenceError(VM::Error(VM::ePropertyNotFoundError, *this
                SF_DEBUG_ARG(args.ArgMN.GetName())
                SF_DEBUG_ARG(args.ArgObject)
                ));
        }
    }
}

void VM::exec_callpropvoid(VMAbcFile& file, UInt32 mn_index, UInt32 arg_count)
{
    // Call a property, discarding the return value.
    
    // Read arguments ...
    ReadArgsMnObject args(file, arg_count, mn_index);
    
    if (IsException())
        return;
    
    // Resolve property ...
    
    PropRef prop;

    FindObjProperty(prop, *this, args.ArgObject, args.ArgMN);

    if (prop)
    {
        Value value;
        
        if (!prop.GetSlotValueUnsafe(*this, value, SlotInfo::valExecute))
            return;
        
        // A TypeError is thrown if the property specified by the
        // multiname is null or undefined.
        if (value.IsNullOrUndefined())
        {
            ThrowTypeError(VM::Error(VM::eCallOfNonFunctionError, *this
                SF_DEBUG_ARG(args.ArgMN.GetName())
                ));
            return;
        }

        // The [[Call]] property is invoked on the value of the resolved property with the arguments 
        // obj, arg1, ..., argn. 

        // We MUST discard result here.
        Execute(value, args.ArgObject, arg_count, args.GetCallArgs(), true);
    }
    else
    {
        // No property ...
        if (GetValueTraits(args.ArgObject).IsDynamic())
        {
            // In case of a dynamic object property might be created.
            // But we do not create it for the time being. We just throw
            // an exception.
            ThrowTypeError(VM::Error(VM::eCallOfNonFunctionError, *this
                SF_DEBUG_ARG(args.ArgMN.GetName())
                ));
            return;
        }
        else
        {
            return ThrowReferenceError(VM::Error(VM::ePropertyNotFoundError, *this
                SF_DEBUG_ARG(args.ArgMN.GetName())
                SF_DEBUG_ARG(args.ArgObject)
                ));
        }
    }
}

void VM::exec_callmethod(UInt32 method_index, UInt32 arg_count)
{
    // Call a method identified by index in the object's method table (virtual table).
    // This opcode cannot be generated by a compiler. Veryfier must throw
    // exception in this case.
    
    // Read arguments ...
    ReadArgsObject args(*this, arg_count);
    
    if (IsException())
        return;
    
    // method_index is the index of the method to invoke on receiver. arg_count is a u30 that is
    // the number of arguments present on the stack. receiver is the object to invoke the method on.
    
    const Traits& tr = GetValueTraits(args.ArgObject);

#if 0
    const Value funct(method_index, vt, Value::kVTableInd);

    // The [[Call]] property is invoked on the value of the resolved property with the arguments 
    // obj, arg1, ..., argn.
    Execute(funct, args.ArgObject, arg_count, args.GetCallArgs());
#else
    ExecuteVTableIndUnsafe(method_index, tr, args.ArgObject, arg_count, args.GetCallArgs());
#endif
}

void VM::exec_callsupermethod(UInt32 method_index, UInt32 arg_count)
{
    // Call a method identified by index in the object's method table (virtual table).
    // This opcode cannot be generated by a compiler. Verifier must throw
    // exception in this case.

    // Read arguments ...
    ReadArgsObject args(*this, arg_count);

    if (IsException())
        return;

    // method_index is the index of the method to invoke on receiver. arg_count is a u30 that is
    // the number of arguments present on the stack. receiver is the object to invoke the method on.

    const Traits* tr = GetCurrCallFrame().GetOriginationTraits();

    if (tr == NULL)
        tr = &GetValueTraits(args.ArgObject);

    const Traits* parent_tr = tr->GetParent();
    if (parent_tr == NULL)
        return ThrowReferenceError(VM::Error(VM::eIllegalSuperCallError, *this
        SF_DEBUG_ARG("Couldn't find parent property")
        ));

#if 0
    const Value funct(method_index, *parent_tr, Value::kVTableInd);

    // The [[Call]] property is invoked on the value of the resolved property with the arguments 
    // obj, arg1, ..., argn. 
    Execute(funct, args.ArgObject, arg_count, args.GetCallArgs());
#else
    ExecuteVTableIndUnsafe(method_index, *parent_tr, args.ArgObject, arg_count, args.GetCallArgs());
#endif
}

void VM::exec_callgetter(UInt32 method_index, UInt32 arg_count)
{
    // Call a getter identified by index in the object's method table (virtual table).
    // This opcode cannot be generated by a compiler. Veryfier must throw
    // exception in this case.

    // Read arguments ...
    ReadArgsObject args(*this, arg_count);

    if (IsException())
        return;

    // method_index is the index of the method to invoke on receiver. arg_count is a u30 that is
    // the number of arguments present on the stack. receiver is the object to invoke the method on.

    const Traits& tr = GetValueTraits(args.ArgObject);
    const VTable& vt = tr.GetVT();

#ifdef USE_VTABLE_IND
    const Value funct_getter(method_index, vt, Value::kVTableInd);
#else
    const Value& funct_getter = vt.GetRaw(AbsoluteIndex(method_index));
#endif

    // Retrieve function.
    Value funct;
    ExecuteUnsafe(funct_getter, args.ArgObject, funct, 0, NULL);

    if (IsException())
        return;

    // The [[Call]] property is invoked on the value of the resolved property with the arguments 
    // obj, arg1, ..., argn.
    Execute(funct, args.ArgObject, arg_count, args.GetCallArgs());
}

void VM::exec_callsupergetter(UInt32 method_index, UInt32 arg_count)
{
    // Call a getter identified by index in the object's method table (virtual table).
    // This opcode cannot be generated by a compiler. Verifier must throw
    // exception in this case.

    // Read arguments ...
    ReadArgsObject args(*this, arg_count);

    if (IsException())
        return;

    // method_index is the index of the method to invoke on receiver. arg_count is a u30 that is
    // the number of arguments present on the stack. receiver is the object to invoke the method on.

    const Traits* tr = GetCurrCallFrame().GetOriginationTraits();

    if (tr == NULL)
        tr = &GetValueTraits(args.ArgObject);

    const Traits* parent_tr = tr->GetParent();
    if (parent_tr == NULL)
        return ThrowReferenceError(VM::Error(VM::eIllegalSuperCallError, *this
        SF_DEBUG_ARG("Couldn't find parent property")
        ));

    const Value funct_getter(method_index, *parent_tr, Value::kVTableInd);

    // Retrieve function.
    Value funct;
    ExecuteUnsafe(funct_getter, args.ArgObject, funct, 0, NULL);

    if (IsException())
        return;

    // The [[Call]] property is invoked on the value of the resolved property with the arguments 
    // obj, arg1, ..., argn. 
    Execute(funct, args.ArgObject, arg_count, args.GetCallArgs());
}

void VM::exec_callstatic(VMAbcFile& file, UInt32 method_index, UInt32 arg_count)
{
    // Call a method identified by index in the abcFile method table.
    
    // Read arguments ...
    ReadArgsObject args(*this, arg_count);
    
    if (IsException())
        return;
    
    // method_index is the index of the method_info of the method to invoke.
            
    // The receiver will be used as the "this" value for the method. 
    // The result of the method is pushed onto the stack.

    {
        const SInt32 mbi_ind = file.GetMethodBodyInfoInd(method_index);
        
#if 0
        AddFrame(
            Value::GetUndefined(), // There is no object to track its life time.
            file,
            mbi_ind,
            args.ArgObject,
            NULL, // ??? No saved scope ???
            arg_count,
            args.GetCallArgs(),
            false, // discard_result
            NULL
            SF_DEBUG_ARG(args.ArgObject.GetObject()->GetName() + " callstatic")
            );
#else
        const Traits& tr = args.ArgObject.GetObject()->GetTraits();
        AddFrame(
            Value::GetUndefined(), // There is no object to track its life time.
            file,
            mbi_ind,
            args.ArgObject,
            arg_count,
            args.GetCallArgs(),
            false, // discard_result
            // NULL, // ??? No saved scope ???
            &tr.GetStoredScopeStack(),
            // NULL
            &tr
            SF_DEBUG_ARG(args.ArgObject.GetObject()->GetName() + " callstatic")
            );
#endif
    }
}

void VM::exec_newfunction(const CallFrame& cf, UInt32 method_ind)
{
    // When creating the new function object the scope stack used is the current scope stack when
    // this instruction is executed, and the body is the method_body entry that references the
    // specified method_info entry.

    // It is OK to take file from a current call frame.
    VMAbcFile& file = cf.GetFile();

    // This is a correct implementation.
    // We HAVE TO combine Saved Scope and Scope Stack.

    // Let's use a stored scope if there is one.
    const ScopeStackType* sss = cf.GetSavedScope();
    ScopeStackType ss(GetMemoryHeap());

    if (sss && !sss->IsEmpty())
        ss = *sss;

    const ScopeStackType& vm_ss = GetScopeStack();
    const UPInt size = vm_ss.GetSize();

    for (UPInt i = GetScopeStackBaseInd(); i < size; ++i)
        ss.PushBack(vm_ss[i]);

    // No exceptions in this method;
    Pickable<Instances::Function> funct = GetClassFunction().MakeInstance(file, method_ind, ss, GetValueTraits(GetGlobalObject()));

    OpStack.PushBack(funct);

    // No exceptions in this method;
    // Tamarin throws exceptions in this opcode.
}

void VM::exec_call(UInt32 arg_count)
{
    // Call a closure.
    
    // Read arguments ...
    ReadArgsObjectValue args(*this, arg_count);
    
    if (IsException())
        return;

    // function is the closure that is being called. receiver is the object to use for the "this" value. This will
    // invoke the [[Call]] property on function with the arguments receiver, arg1, ..., argn. 
    // The result of invoking the [[Call]] property will be pushed onto the stack.

    Execute(args.value, args.ArgObject, arg_count, args.GetCallArgs());
}

void VM::exec_callobject(UInt32 arg_count)
{
    // Read arguments ...
    ReadArgsObjectRef args(*this, arg_count);

    if (IsException())
        return;

#if 0
    ExecuteInternalUnsafe(args.ArgObject, Value::GetUndefined(), args.ArgObject, arg_count, args.GetCallArgs());
#else
    //SF_ASSERT(args.ArgObject.IsClass());
    args.ArgObject.GetObject()->Call(Value::GetUndefined(), args.ArgObject, arg_count, args.GetCallArgs());
#endif
}

void VM::exec_callsuper(VMAbcFile& file, UInt32 mn_index, UInt32 arg_count)
{
    // Call a method on a base class.
    
    // Read arguments ...
    ReadArgsMnObject args(file, arg_count, mn_index);
    
    if (IsException())
        return;
    
    // The base class of receiver is determined and the method indicated by the multiname is
    // resolved in the declared traits of the base class.

    Value func;
    if (!GetSuperProperty(*this, GetCurrCallFrame().GetOriginationTraits(), func, args.ArgObject, args.ArgMN, SlotInfo::valExecute))
        // Not confirmed ...
        return ThrowReferenceError(VM::Error(VM::eCallNotFoundError, *this
            SF_DEBUG_ARG(args.ArgMN.GetName())
            ));

    // The [[Call]] property is invoked on the value of the resolved property with the arguments 
    // obj, arg1, ..., argn. 
    // The first argument will be used as the "this" value for the method.
    // The result of the method call is pushed onto the stack.
    
    Execute(func, args.ArgObject, arg_count, args.GetCallArgs());
}

void VM::exec_callsupervoid(VMAbcFile& file, UInt32 mn_index, UInt32 arg_count)
{
    // Call a method on a base class, discarding the return value.
    
    // Read arguments ...
    ReadArgsMnObject args(file, arg_count, mn_index);
    
    if (IsException())
        return;
    
    // The base class of receiver is determined and the method indicated by the multiname is
    // resolved in the declared traits of the base class.

    Value value;
    if (!GetSuperProperty(*this, GetCurrCallFrame().GetOriginationTraits(), value, args.ArgObject, args.ArgMN, SlotInfo::valExecute))
        // Not confirmed ...
        return ThrowReferenceError(VM::Error(VM::eCallNotFoundError, *this
            SF_DEBUG_ARG(args.ArgMN.GetName())
            ));

    // The [[Call]] property is invoked on the value of the resolved property with the arguments 
    // obj, arg1, ..., argn. 
    // The first argument will be used as the "this" value for the method.
    // The result of the method call is pushed onto the stack.
    
    // We MUST discard result here.
    Execute(value, args.ArgObject, arg_count, args.GetCallArgs(), true);
}

void VM::exec_construct(UInt32 arg_count)
{
    // Construct an instance.
    
    // Read arguments ...
    // ReadArgsObjectRef doesn't work here.
    ReadArgsObjectRef args(*this, arg_count);
    
    if (IsException())
        return;
    
    // In case we can use more efficient code here.
    SF_ASSERT(!args.ArgObject.IsTraits());

    // "object" is the function that is being constructed. This will invoke the [[Construct]] property on object with
    // the given arguments. The new instance generated by invoking [[Construct]] will be pushed onto the stack.
    
    // TODO:
    // !!! Look up for a "Construct" property ...
    //A TypeError is thrown if object does not implement the [[Construct]] property.
    
    if (args.ArgObject.IsNullOrUndefined())
        return ThrowTypeError(VM::Error(VM::eConvertNullToObjectError, *this));

    const Value::KindType kind = args.ArgObject.GetKind();
    if (kind == Value::kVTableInd || kind == Value::kVTableIndClosure)
        return ThrowTypeError(VM::Error(VM::eCannotCallMethodAsConstructor, *this
        SF_DEBUG_ARG(GetValueTraits(args.ArgObject).GetName())
        ));

    if (!args.ArgObject.IsObject())
        return ThrowTypeError(VM::Error(VM::eNotConstructorError, *this
        SF_DEBUG_ARG(args.ArgObject)
        ));

    args.ArgObject.GetObject()->Construct(args.ArgObject, arg_count, args.GetCallArgs());
}

void VM::exec_constructsuper(const CallFrame& cf, UInt32 arg_count)
{
    // Construct an instance of the base class.
    // This will invoke the constructor on the base class of object with 
    // the given arguments.
    
    // Read arguments ...
    ReadArgsObject args(*this, arg_count);
    
    if (IsException())
        return;
    
    const Traits* ot = cf.GetOriginationTraits();
    SF_ASSERT(ot);

    /* Old code.
    // Do not delete. Keep for reference.
    const Class& cl = ot->GetClass();

    SF_ASSERT(cl.GetParentClass());
    if (cl.GetParentClass())
    {
        Class& parent_class = *cl.GetParentClass();
        
        // This will invoke the constructor on the base class of object with the given arguments.
        parent_class.GetNewObjectTraits().Super(*ot, args.ArgObject, arg_count, args.GetCallArgs());
    }
    */

    if (ot->GetParent())
    {
        // Dirty trick.
        // constructsuper can be called only for instances, so we can cast
        // Traits to InstanceTraits.
        const InstanceTraits::Traits* ptr = static_cast<const InstanceTraits::Traits*>(ot->GetParent());

        ptr->AS3Constructor(*ot, args.ArgObject, arg_count, args.GetCallArgs());
    }
}

void VM::exec_constructprop(VMAbcFile& file, UInt32 mn_index, UInt32 arg_count)
{
    // Construct a property.

    // The [[Construct]] property is invoked on the value of the resolved property with the arguments
    // obj, arg1, ..., argn. 
    // The new instance generated by invoking [[Construct]] will be pushed onto the stack.          
    
    // Read arguments ...
    ReadArgsMnObjectRef args(file, arg_count, mn_index);
    
    if (IsException())
        return;

    if (args.ArgMN.IsQName())
    {
        const ClassTraits::Traits* ctr = Resolve2ClassTraits(args.ArgMN);

        if (ctr)
        {
            InstanceTraits::Traits& itr = ctr->GetInstanceTraits();

            itr.GetClass().Construct(args.ArgObject, arg_count, args.GetCallArgs());
            return;
        }
    }

    // Fall back to the regular version.

    PropRef prop;

    FindObjProperty(prop, *this, args.ArgObject, args.ArgMN);

    if (prop)
    {
        Value value;

        if (!prop.GetSlotValueUnsafe(*this, value))
            return;

        if (value.IsNullOrUndefined())
            return ThrowTypeError(VM::Error(VM::eConvertNullToObjectError, *this));

        const Value::KindType kind = value.GetKind();
        if (kind == Value::kVTableInd || kind == Value::kVTableIndClosure)
            return ThrowTypeError(VM::Error(VM::eCannotCallMethodAsConstructor, *this
            SF_DEBUG_ARG(args.ArgMN.GetName())
            ));

        // TODO:
        // !!! Look up for a "Construct" property ...
        //A TypeError is thrown if object does not implement the [[Construct]] property.

        // We may not use Construct() from Traits here because value can be 
        // a constructor function. And constructor functions have to be objects.
        value.GetObject()->Construct(args.ArgObject, arg_count, args.GetCallArgs());
    } 
    else
    {
        return ThrowReferenceError(VM::Error(VM::ePropertyNotFoundError, *this
            SF_DEBUG_ARG(args.ArgMN.GetName())
            SF_DEBUG_ARG(args.ArgObject)
            ));
    }
}

void VM::exec_getdescendants(VMAbcFile& file, UInt32 mn_index) 
{
    // XML - related ...
    
    // Read arguments ...
    ReadMnObjectRef args(file, mn_index);
    
    if (IsException())
        return;
    
    // Not finished yet ...
    //SF_ASSERT(false);
    
    // A TypeError is thrown if obj is not of type XML or XMLList.

    // !!! This is a wrong result !!!
    args.ArgObject.SetNull();
}

void VM::exec_newcatch(VMAbcFile& file, const Abc::MethodBodyInfo::ExceptionInfo& e)
{
    SF_ASSERT(TraitsCatch.GetPtr());
    Classes::Catch& cl = (Classes::Catch&)TraitsCatch->GetInstanceTraits().GetClass();
    // This MakeInstance() should not necessary be implemented in Class.
    OpStack.PushBack(cl.MakeInstance(file, e));

    // No exceptions in this method;
    // Tamarin throws exceptions in this opcode.
}

void VM::FindProperty(PropRef& result, const Multiname& mn)
{
    FindScopeProperty(result, *this, GetScopeStackBaseInd(), GetScopeStack(), mn);

    // Look in Saved Scope.
    if (!result)
    {
#ifdef SF_AS3_ENABLE_CALLFRAME_CACHE
        const ScopeStackType* ss = CallStack.Back()->GetSavedScope();
#else
        const ScopeStackType* ss = CallStack.Back().GetSavedScope();
#endif

        if (ss)
            FindScopeProperty(result, *this, 0, *ss, mn);
    }

    // Look in Global Objects. This is correct behavior.
    if (!result)
    {
        const ClassTraits::Traits* ctr = GetRegisteredClassTraits(mn);

#if 0 // Future development.
        if (ctr && ctr->IsValid() && ctr->GetInstanceTraits().HasConstructorSetup())
        {
            result = PropRef(&ctr->GetInstanceTraits().GetClass(), NULL, 0);
            return;
        }
#endif

        FindGOProperty(result, *this, GetGlobalObjects(), mn, ctr);
    }
}

void VM::exec_findpropstrict(VMAbcFile& file, UInt32 mn_index) 
{
    ReadMn args(file, mn_index);
    
    if (IsException())
        return;

    // This searches the scope stack, and then the saved scope in the current method closure, for a
    // property with the name specified by the multiname at mn_index.
    
    // Find a property.
    PropRef prop;
    FindProperty(prop, args.ArgMN);

    if (prop)
    {
        // Push found object ...
        OpStack.PushBack(prop.GetThis());
    } else
    {
        // A ReferenceError is thrown if the property is not resolved in any object on the scope stack.
        // return ThrowReferenceError("The property is not resolved in any object on the scope stack");

        return ThrowReferenceError(VM::Error(VM::eUndefinedVarError, *this
            SF_DEBUG_ARG(args.ArgMN.GetName())
            ));
    }
}

void VM::exec_findproperty(VMAbcFile& file, UInt32 mn_index) 
{
    // Search the scope stack for a property.
    
    ReadMn args(file, mn_index);

    if (IsException())
        return;

    // This searches the scope stack, and then the saved scope in the current method closure, for a
    // property with the name specified by the multiname at mn_index.
    
    // If the property is resolved then the object it was resolved in is pushed onto the stack. If the
    // property is unresolved in all objects on the scope stack then the global object is pushed onto
    // the stack.

#if 0
    // We shouldn't put a Class on stack. We should put a global object responsible for this class instead.
    const ClassTraits::Traits* ctr = FindClassTraits(*this, args.ArgMN);
    if (ctr && ctr->IsValid() && ctr->GetInstanceTraits().HasConstructorSetup())
        // Push found object ...
        return OpStack.PushBack(Value(&ctr->GetInstanceTraits().GetClass()));
#endif

    PropRef prop;
    FindProperty(prop, args.ArgMN);

    if (prop)
    {
        // Push found object ...
        OpStack.PushBack(prop.GetThis());
    } else
    {
        // Push GlobalObject ...
        OpStack.PushBack(GetGlobalObject());
    }
}

void VM::exec_getlex(VMAbcFile& file, UInt32 mn_index) 
{
    // Find and get a property.
    
    ReadMnCt args(file, mn_index);
    
    if (IsException())
        return;
    
    // This is the equivalent of doing a "findpropstict" followed by a "getproperty". It will find the
    // object on the scope stack that contains the property, and then will get the value from that object.

    // Find a property.
    // The same as "findpropstict" ...

    const Multiname mn(file, args.ArgMN);

#if 0
    // There is no need to do this because case with classes will be handled by Tracer.
    // This should be safe because Class is a value we want to get.
    const ClassTraits::Traits* ctr = FindClassTraits(*this, mn);
    if (ctr && ctr->IsValid() && ctr->GetInstanceTraits().HasConstructorSetup())
        // Push found object ...
        return OpStack.PushBack(Value(&ctr->GetInstanceTraits().GetClass()));
#endif

    PropRef prop;
    FindProperty(prop, mn);

    if (prop)
    {
        // ... and then get the value from this object.

        // Efficient version.
//         OpStack.PushBack(Value::GetUndefined());
//         prop.GetValue(OpStack.Back());
//         if (IsException())
//             return OpStack.PopBack();

        // Current version.
        Value value;

        if (!prop.GetSlotValueUnsafe(*this, value))
            return;

        // DO NOT delete this code.
//         // That should be already handled by GetValue().
//         switch (value.GetKind())
//         {
//         case Value::kFunction:
//             value = GetClassFunction().MakeInstance2(value.AsFunction(), prop.GetObject() SF_DEBUG_ARG(value.AsFunction().GetFunctionName()));
//             break;
//         case Value::kThunk:
//             value = GetClassFunction().MakeInstance(
//                 (InstanceTraits::Traits&)prop.GetObject()->GetValueTraits(),
//                 *prop.GetObject(), 
//                 value.AsThunk()
//                 );
//             break;
//         default:
//             break;
//         }

        OpStack.PushBack(value);
    } else
    {
        // A ReferenceError is thrown if the property is not resolved in any object on the scope stack.
        return ThrowReferenceError(VM::Error(VM::ePropertyNotFoundError, *this
            SF_DEBUG_ARG(args.ArgMN.GetName(file.GetConstPool()).ToCStr())
            SF_DEBUG_ARG("any object on the scope stack")
            ));
    }
}

void VM::exec_getproperty(VMAbcFile& file, UInt32 mn_index) 
{
    // Get a property.
    
    // Read arguments ...
    ReadMnObjectRef args(file, mn_index);
    
    if (IsException())
        return;
    
    // The property with the name specified by the multiname will be resolved in object, and the
    // value of that property will be pushed onto the stack. If the property is unresolved,
    // undefined is pushed onto the stack.
    
    Value _this(args.ArgObject, PickValue);
    if(!AS3::GetPropertyUnsafe(*this, _this, args.ArgMN, args.ArgObject))
    {
        if (IsException())
            return;

        // This logic seems to be specific to Tamarin.
        if (_this.IsPrimitive())
        {
            return ThrowReferenceError(VM::Error(VM::ePropertyNotFoundError, *this
                SF_DEBUG_ARG(args.ArgMN.GetName())
                SF_DEBUG_ARG(_this)
                ));
        }
    }
}

void VM::exec_initproperty(VMAbcFile& file, UInt32 mn_index) 
{
    // Initialize a property.
    
    // Read arguments ...
    ReadValueMnObject args(file, mn_index);
    
    if (IsException())
        return;
    
    InitializerGuard __(*this);

    AS3::SetProperty(*this, args.ArgObject, args.ArgMN, args.ArgValue).DoNotCheck();
}

void VM::exec_deleteproperty(VMAbcFile& file, UInt32 mn_index) 
{
    // Delete a property.
    
    // Read arguments ...
    ReadMnObjectRef args(file, mn_index);

    // TODO:
    // A ReferenceError is thrown if object is null or undefined.
    // It is TypeError for now.

    if (IsException())
        return;

    // This will invoke the [[Delete]] method on object with the name specified by the multiname.
    // If object is not dynamic or the property is a fixed property then nothing happens, and false
    // is pushed onto the stack. If object is dynamic and the property is not a fixed property, it is
    // removed from object and true is pushed onto the stack.
    bool result = false;

    if (args.ArgObject.IsObject())
    {
        Object& obj = *args.ArgObject.GetObject();

        if (obj.IsDynamic())
            result = obj.DeleteProperty(args.ArgMN);

        if (IsException())
            return;
    }
    else if (args.ArgObject.IsPrimitive())
    {
        // We want to bypass a thunk here.
        // This logic seems to be Tamarin-specific.
        return ThrowReferenceError(VM::Error(VM::eDeleteSealedError, *this
                SF_DEBUG_ARG(args.ArgMN.GetName())
                SF_DEBUG_ARG(args.ArgObject)
                ));
    }

    // All primitive values are also sealed classes.

    args.ArgObject.SetBool(result);
}

void VM::exec_getslot(UInt32 slot_index) 
{
    // Get the value of a slot.
    
    // Read arguments ...
    ReadObjectRef args(*this);
    
    if (IsException())
        return;
    
    SF_ASSERT(args.ArgObject.IsObject());
    const Value _this(args.ArgObject, PickValue);
    _this.GetObject()->GetSlotValueUnsafe(SlotIndex(slot_index), args.ArgObject).DoNotCheck();
}

void VM::exec_setabsslot(UPInt slot_ind)
{
    // Set the value of a slot.
    // slot_ind is ONE based.
    // slot_ind - 1 is an index in a slot table.

    // Read arguments ...
    ReadValueObject args(*this);

    if (IsException())
        return;

    SF_ASSERT(args.ArgObject.IsObject());
    Object& obj = *args.ArgObject.GetObject();

    obj.GetTraits().SetSlotValue(AbsoluteIndex(slot_ind - 1), args.ArgValue, &obj).DoNotCheck();
}

void VM::exec_initabsslot(UPInt slot_ind)
{
    // Set the value of a slot.
    // slot_ind is ONE based.
    // slot_ind - 1 is an index in a slot table.

    // Read arguments ...
    ReadValueObject args(*this);

    if (IsException())
        return;

    SF_ASSERT(args.ArgObject.IsObject());
    Object& obj = *args.ArgObject.GetObject();

    InitializerGuard __(*this);

    obj.GetTraits().SetSlotValue(AbsoluteIndex(slot_ind - 1), args.ArgValue, &obj).DoNotCheck();
}

void VM::exec_setslot(UInt32 slot_index) 
{
    // Set the value of a slot.
    
    // Read arguments ...
    ReadValueObject args(*this);
    
    if (IsException())
        return;
    
    args.ArgObject.GetObject()->SetSlotValue(SlotIndex(slot_index), args.ArgValue).DoNotCheck();
}

void VM::exec_coerce(VMAbcFile& file, UInt32 mn_index) 
{
    // Coerce a value to a specified type.
    
    // Read arguments ...
    ReadMnCtValueRef args(file, mn_index);
    
    if (IsException())
        return;
    
    // The type specified by the multiname is resolved, and value is coerced to that type. The
    // resulting value is pushed onto the stack. If any of value’s base classes, or implemented
    // interfaces matches the type specified by the multiname, then the conversion succeeds and the
    // result is pushed onto the stack.
    
    // Resolve multiname ...
    const ClassTraits::Traits* to = Resolve2ClassTraits(file, args.ArgMN);
    
    if (to)
    {
#if 0
        // We MAY NOT use args.value as a source and a target (aliased).
        // Coerce() expects these values to be separate values.
        Value result;
        if (to->Coerce(args.value, result))
        {
            result.Swap(args.value);
            return;
        }
#else
        // Aliasing seems to be fine for the time being.
        if (to->Coerce(args.value, args.value))
            return;
#endif
        else
        {
            // A TypeError is thrown if value cannot be coerced to the specified type.
            return ThrowTypeError(VM::Error(VM::eCheckTypeFailedError, *this
                SF_DEBUG_ARG(args.value)
                SF_DEBUG_ARG(to->GetName().ToCStr())
                ));
        }
    }
    
    return ThrowReferenceError(VM::Error(VM::ePropertyNotFoundError, *this
        SF_DEBUG_ARG(args.ArgMN.GetName(file.GetConstPool()).ToCStr())
        SF_DEBUG_ARG("any object on the scope stack")
        ));
}

void VM::exec_newobject(UInt32 arg_count) 
{
    Pickable<Instances::Object> o = MakeObject();
    
    for (UInt32 i = 0; i < arg_count; ++i)
    {
        Value value(OpStack);
        Value name(OpStack);

        // All object properties are dynamic.
        o->AddDynamicSlotValuePair(name.AsString(), value);
    }
    
    OpStack.PushBack(o);

    // It looks like this function doesn't throw exceptions.
    // Tamarin throws exceptions in this opcode.
}

void VM::exec_newclass(VMAbcFile& file, UInt32 v) 
{
    const Abc::ClassInfo& class_info = file.GetClasses().Get(v);
    
    Value& value = OpStack.Top0();
    
    // TBD:
    // The base_type argument must be coerced to Class and then must be a base class 
    // of class_info. This means that there is no automatic creation of base classes,
    // instead compiler is responsible for creating base class instance ahead of time
    // and passing it to us.
    // NOTE: newclass is also called for interfaces,
    // in which case base_type is typically null.

    if (value.IsNullOrUndefined())
    {
        if (class_info.HasSuperClass())
            return ThrowTypeError(VM::Error(VM::eConvertNullToObjectError, *this));
    }
    else
    {
        if (!value.IsClass())
            // Is this a correct exception type and a message?
            return ThrowTypeError(VM::Error(VM::eConvertNullToObjectError, *this));
    }

    // check for *scaleform extension* packages.
    const Abc::Multiname& name = class_info.GetName(file.GetConstPool());
    Instances::Namespace& t_ns = file.GetInternedNamespace(name.GetNamespaceInd());
    const ASString& t_uri = t_ns.GetUri();
    const StringDataPtr t_str(t_uri.ToCStr(), t_uri.GetSize());
    const StringDataPtr scaleform_gfx("scaleform.gfx");

    if (t_str.GetSize() >= scaleform_gfx.GetSize() && SFstrncmp(t_str.ToCStr(), scaleform_gfx.ToCStr(), scaleform_gfx.GetSize()) == 0)
    {
        // This is *scaleform.gfx extension* package.
        const ASString t_name = file.GetInternedString(name.GetNameInd());

        if (!GetGlobalObjectCPP().GetProperty(Multiname(t_ns, t_name), value))
        {
            return ThrowReferenceError(VM::Error(VM::ePropertyNotFoundError, *this
                SF_DEBUG_ARG(t_name.ToCStr())
                SF_DEBUG_ARG(scaleform_gfx.ToCStr())
                ));
        }
    }
    else
    {
        // When this instruction is executed, the scope stack must contain all the scopes of all base
        // classes, as the scope stack is saved by the created ClassClosure.

        ClassTraits::UserDefined& cud = GetUserDefinedTraits(file, class_info);

        if (cud.GetInstanceTraits().HasConstructorSetup())
            // This class was already created by another script. It happens.
            value = &cud.GetInstanceTraits().GetConstructor();
        else
            value = cud.MakeClass();
    }

}

void VM::exec_astype(VMAbcFile& file, UInt32 mn_index) 
{
    // Return the same value, or null if not of the specified type.
    
    // Read arguments ...
    ReadMnCtValueRef args(file, mn_index);
    
    if (IsException())
        return;
    
    // Pop value off of the stack. If value is of the type specified by the multiname, push value back
    // onto the stack. If value is not of the type specified by the multiname, then push null onto
    // the stack.
    
    const ClassTraits::Traits* tr = Resolve2ClassTraits(file, args.ArgMN);
    
    // and must be the name of a type ...
    if (tr)
    {
        const ClassTraits::Traits& value_tr = GetClassTraits(args.value);
        
        if (tr != &value_tr)
        {
            args.value.SetNull();
            return;
        }
    }
    
    return ThrowTypeError(VM::Error(VM::eClassNotFoundError, *this
        SF_DEBUG_ARG(args.ArgMN.GetName(file.GetConstPool()).ToCStr())
        ));
}

void VM::exec_instanceof() 
{
    // Check the prototype chain of an object for the existence of a type.

    Value type(OpStack);

    if (type.IsFunction() || type.IsClass())
    {
        Value& value = OpStack.Top0();
        Value& result = value;

        if (value.IsNullOrUndefined())
            return result.SetBool(false);

        const Traits* cur_tr = &GetClassTraits(value);
        const Traits& type_tr = GetValueTraits(type);

        if (type.IsClass())
        {
            // Check parents.
            while (cur_tr)
            {
                if (cur_tr == &type_tr)
                    return result.SetBool(true);

                cur_tr = cur_tr->GetParent();
            }
        }
        else
        {
            // Check prototype chain.
            const Class&  type_cl = type_tr.GetClass();

            while (cur_tr)
            {
                AS3::Class& cur_cl = const_cast<Traits*>(cur_tr)->GetClass();
                const AS3::Object& proto = cur_cl.GetPrototype();

                // "type" can be a primitive value.
                if (&proto == &type_cl)
                    return result.SetBool(true);

                cur_tr = cur_tr->GetParent();
            }
        }

        result.SetBool(false);
    }
    else
        ThrowTypeError(VM::Error(VM::eCantUseInstanceofOnNonObjectError, *this));
}

void VM::exec_istype(VMAbcFile& file, UInt32 mn_index) 
{
    // Check whether an Object is of a certain type.
    
    // Read arguments ...
    ReadMnCtValueRef args(file, mn_index);
    // No exceptions at this point.
    
    const ClassTraits::Traits* type = Resolve2ClassTraits(file, args.ArgMN);
    
    if (type == NULL)
        // Unresolved multiname ...
        return ThrowTypeError(VM::Error(VM::eClassNotFoundError, *this
            SF_DEBUG_ARG(args.ArgMN.GetName(file.GetConstPool()).ToCStr())
            ));
    
    // Resolve the type specified by the multiname. Let indexType refer to that type. Compute the
    // type of value, and let valueType refer to that type. If valueType is the same as indexType, result
    // is true. If indexType is a base type of valueType, or an implemented interface of valueType,
    // then result is true. Otherwise result is set to false. Push result onto the stack.
    
    args.value.SetBool(IsOfType(args.value, *type));
}

void VM::exec_debugline(CallFrame& cf, UInt32 v)
{
#ifdef SF_AMP_SERVER
    AMP::ViewStats* stats = GetAdvanceStats();
    if (stats != NULL && 
        AmpServer::GetInstance().IsProfiling() && 
        AmpServer::GetInstance().GetProfileLevel() >= Amp_Profile_Level_ActionScript)
    {
        SetActiveLine(v);
        UInt32 fileId = cf.GetFile().GetAbcFile().GetFileHandle() + (cf.GetMethodBodyInfo().GetMethodInfoInd() << 16);
        stats->RegisterScriptFunction(fileId, cf.GetFile().GetAbcFile().GetSwfFileOffset(), cf.Name->pData, 0, 3, true);
        if (stats->IsDebugPaused())
        {
            AmpServer::GetInstance().SendCurrentState();
        }
        stats->DebugWait();
    }

    cf.CurrLineNumber = v;
#else
    SF_UNUSED2(cf, v);
#endif
}

void VM::exec_debugfile(CallFrame& cf, UInt32 v)
{
#ifdef SF_AMP_SERVER
    VMAbcFile& file = cf.GetFile();

    AMP::ViewStats* stats = GetAdvanceStats();
    if (stats != NULL && 
        AmpServer::GetInstance().IsProfiling() && 
        AmpServer::GetInstance().GetProfileLevel() >= Amp_Profile_Level_ActionScript)
    {
        stats->RegisterSourceFile(file.GetAbcFile().GetFileHandle(), v, file.GetInternedString(v).ToCStr());

        UInt64 fileId = file.GetAbcFile().GetFileHandle();
        fileId <<= 32;
        fileId += v;
        SetActiveFile(fileId);
    }

    cf.CurrFileInd = v;
#else
    SF_UNUSED2(cf, v);
#endif
}

void VM::exec_astypelate() 
{
    // Return the same value, or null if not of the specified type.
    // (Similar to "astype") ...
    
    // Pop class and value off of the stack. class should be an object of type Class. If value is of the
    // type specified by class, push value back onto the stack. If value is not of the type specified by
    // class, then push null onto the stack.
    
    const Value vclass(OpStack);
    
    if (!vclass.IsClass())
    {
        // A TypeError is thrown if class is not of type Class.
        if (vclass.IsNullOrUndefined())
        {
            return ThrowTypeError(VM::Error(
                vclass.IsNull() ? eConvertNullToObjectError :  eConvertUndefinedToObjectError,
                *this
                ));
        }

        return ThrowTypeError(VM::Error(VM::eIsTypeMustBeClassError, *this));
    }
    
    const ClassTraits::Traits& tr = vclass.AsClass().GetClassTraits();
    Value& value = OpStack.Top0();
    
    if (!IsOfType(value, tr))
        value.SetNull();
}

void VM::exec_newarray(UInt32 arr_size) 
{
    Pickable<Instances::Array> a = MakeArray();
    
    a->Pick(OpStack, arr_size);
    
    OpStack.PushBack(a);

    // No exceptions in this method;
    // Tamarin throws exceptions in this opcode.
}

void VM::exec_hasnext2(UInt32 object_reg, UInt32 index_reg) 
{
    AbsoluteIndex reg_ind(index_reg);
    AbsoluteIndex obj_ind(object_reg);
    Value& obj_value = GetRegister(obj_ind);

    if (reg_ind.Get() == obj_ind.Get())
        return ThrowTypeError(VM::Error(VM::eInvalidHasNextError, *this));

    // Check for null/undefined
    if (obj_value.IsNullOrUndefined())
        // Push false.
        return OpStack.PushBack(Value(false));

    UInt32 v = 0;
    if (!GetRegister(reg_ind).Convert2UInt32(v))
        // Exception
        return;

    GlobalSlotIndex slot_ind(v);

    if (obj_value.IsObject())
    {
        Object& obj = obj_value;
        
        GlobalSlotIndex ind = obj.GetNextDynPropIndex(slot_ind);
        Object* cur_obj = &obj;

        const Traits* cur_tr = &obj.GetTraits();
        // Go inside if we have no more attributes to enumerate.
        while (cur_tr && !ind.IsValid())
        {
            // Try to enumerate prototype.
            cur_obj = &const_cast<Class&>(cur_tr->GetClass()).GetPrototype();

            ind = cur_obj->GetNextDynPropIndex(GlobalSlotIndex(0));
            // Check for a parent.
            cur_tr = cur_tr->GetParent();

            // If there is no more properties to enumerate, and there is no
            // parent, then stop.
        }

        // Set object.
        if (ind.IsValid())
        {
            if (cur_obj != &obj)
                SetRegister(obj_ind, Value(cur_obj));
        }
        else
            // Set Object to NULL.
            SetRegister(obj_ind, Value::GetNull());

        // Set index.
        SetRegister(reg_ind, Value(ind.Get()));

        // Store boolean result on stack.
        OpStack.PushBack(Value(ind.IsValid()));
    }
    else
    {
        // Primitive values.

#if 0
        Traits& t = GetValueTraits(obj_value);
        GlobalSlotIndex ind = t.GetNextDynPropIndex(slot_ind);

        Object* cur_obj = NULL;
        const Traits* cur_tr = &t;
        while (cur_tr && !ind.IsValid())
        {
            cur_obj = &const_cast<Class&>(cur_tr->GetClass()).GetPrototype();

            ind = cur_obj->GetNextDynPropIndex(GlobalSlotIndex(0));
            cur_tr = cur_tr->GetParent();
        }

        // Set object.
        if (ind.IsValid())
        {
            if (cur_obj != NULL)
                // Prototype object was found.
                SetRegister(obj_ind, Value(cur_obj));
        }
        else
            // Set Object to NULL.
            SetRegister(obj_ind, Value::GetNull());

        // Set index.
        SetRegister(reg_ind, Value(ind.Get()));

        // Store boolean result on stack.
        OpStack.PushBack(Value(ind.IsValid()));
#endif

        // Traits only.
        GlobalSlotIndex ind = slot_ind;
        const Traits* cur_tr = &GetValueTraits(obj_value);
        Object* cur_obj = NULL;

        // Go inside if we have no more attributes to enumerate.
        do {
            // Try to enumerate prototype.
            cur_obj = &const_cast<Class&>(cur_tr->GetClass()).GetPrototype();

            ind = cur_obj->GetNextDynPropIndex(GlobalSlotIndex(0));
            // Check for a parent.
            cur_tr = cur_tr->GetParent();

            // If there is no more properties to enumerate, and there is no
            // parent, then stop.
        }
        while (cur_tr && !ind.IsValid());

        // Set object.
        if (ind.IsValid())
        {
            SetRegister(obj_ind, Value(cur_obj));
        }
        else
            // Set Object to NULL.
            SetRegister(obj_ind, Value::GetNull());

        // Set index.
        SetRegister(reg_ind, Value(ind.Get()));

        // Store boolean result on stack.
        OpStack.PushBack(Value(ind.IsValid()));
    }
}

void VM::exec_applytype(UInt32 arg_count) 
{
    // Read arguments ...
    ReadArgsObjectRef args(*this, arg_count);

    if (IsException())
        return;

    if (!args.ArgObject.IsClass())
        return ThrowTypeError(VM::Error(eTypeAppOfNonParamType, *this));

    args.ArgObject = &args.ArgObject.AsClass().ApplyTypeArgs(args.GetCallArgsNum(), args.GetCallArgs());
}

void VM::ExecuteInternalUnsafe(const Value& func, const Value& _this, Value& result, unsigned argc, const Value* argv, bool result_on_stack)
{
    SIMD::IS::PrefetchObj(&func);
    SIMD::IS::PrefetchObj(&_this);

    switch(func.GetKind())
    {
    case Value::kFunction:
        {
            Instances::Function& f = func;
            
            // The [[Call]] property is invoked on the value of the resolved property with the arguments 

            if (result_on_stack)
                // Result will be left on stack.
           
				f.Execute(_this, argc, argv);
            else
                f.ExecuteUnsafe(_this, result, argc, argv);
        }
        break;
    case Value::kClass:
    case Value::kObject:
        {
            // It doesn't look like a function ...
            // Just call a "Call" method ...
            
            if (func.GetObject() == NULL)
            {
                return ThrowTypeError(VM::Error(VM::eCallOfNonFunctionError, *this
                    SF_DEBUG_ARG(func)
                    ));
            }

#ifdef SF_FPE_ENABLE
            FPEGuard fpe_guard;
#endif
            func.GetObject()->Call(_this, result, argc, argv);

            // C++. We need to handle exceptions ...
            if (IsException())
                return;
            
            if (result_on_stack)
                OpStack.PickPushBack(result);
        }
        break;
    case Value::kThunk:
        {
            SIMD::IS::PrefetchObj(&func.AsThunk());
            const ThunkInfo& thunk = func.AsThunk();

            ExecuteThunkUnsafe(thunk, _this, result, argc, argv, result_on_stack);
        }
        break;
    case Value::kThunkFunction:
        {
            // ThunkClosure behaves similar to MethodClosure.
            Instances::ThunkFunction& f = func;
            
            f.ExecuteUnsafe(_this, result, argc, argv);
            
            // C++. We need to handle exceptions ...
            if (IsException())
                return;
            
            if (result_on_stack)
                OpStack.PickPushBack(result);
        }
        break;
    case Value::kThunkClosure:
        {
            SIMD::IS::PrefetchObj(&func.GetThunkFunct());
            const ThunkInfo& thunk = func.GetThunkFunct();
            const Value _this(func.GetClosure());

            ExecuteThunkUnsafe(thunk, _this, result, argc, argv, result_on_stack);
        }
        break;
    case Value::kVTableInd:
        {
            const VTable& vt = func.GetTraits().GetVT();
            const SInt32 ind = func.GetVTableInd();
            const Value& real_func = vt.GetRaw(AbsoluteIndex(ind));
            SIMD::IS::PrefetchObj(&real_func);

            // VTable stores MethodInd or Thunk.
            if (real_func.GetKind() == Value::kMethodInd)
            {
                // MethodInd.
                ExecuteMethodIndUnsafe(func, real_func, _this, result, argc, argv, result_on_stack SF_DEBUG_ARG(ind));
            }
            else
            {
                // Thunk.

                SIMD::IS::PrefetchObj(&real_func.AsThunk());
                const ThunkInfo& thunk = real_func.AsThunk();

                ExecuteThunkUnsafe(thunk, _this, result, argc, argv, result_on_stack);
            }
        }
        break;
    case Value::kVTableIndClosure:
        {
            const VTable& vt = func.GetClosure()->GetVT();
            const SInt32 ind = func.GetVTableInd();
            const Value& real_func = vt.GetRaw(AbsoluteIndex(ind));
            SIMD::IS::PrefetchObj(&real_func);
            const Value _this(func.GetClosure());

            // VTable stores MethodInd or Thunk.
            if (real_func.GetKind() == Value::kMethodInd)
            {
                // MethodInd.
                ExecuteMethodIndUnsafe(func, real_func, _this, result, argc, argv, result_on_stack SF_DEBUG_ARG(ind));
            }
            else
            {
                // Thunk.

                SIMD::IS::PrefetchObj(&real_func.GetThunkFunct());
                const ThunkInfo& thunk = real_func.GetThunkFunct();

                ExecuteThunkUnsafe(thunk, _this, result, argc, argv, result_on_stack);
            }
        }
        break;
    default:
        ThrowTypeError(VM::Error(VM::eCallOfNonFunctionError, *this
            SF_DEBUG_ARG(func)
            ));
        break;
    }
}

void VM::ExecuteVTableIndUnsafe(UInt32 ind, const Traits& tr, Value& _this, unsigned argc, const Value* argv)
{
    const Value& real_func = tr.GetVT().GetRaw(AbsoluteIndex(ind));
    SIMD::IS::PrefetchObj(&real_func);

#if 0
    // It is not correct to convert Closure to Object here.
    // No explanation for the time being.
    if (_this.IsClosure())
        _this.Assign(_this.GetClosure()) ;
#endif

    // VTable stores MethodInd or Thunk.
    if (real_func.GetKind() == Value::kMethodInd)
    {
        // MethodInd.
        // We keep this code inlined because we do not want to create temporary
        // Value result.
        const Value func(ind, tr, Value::kVTableInd);

        const SInt32 method_ind = real_func.GetMethodInd();
        const AS3::Traits& real_tr = real_func.GetTraits();
        SF_ASSERT(real_tr.GetFilePtr());
        VMAbcFile& file = *real_tr.GetFilePtr();
        const SInt32 mbi_ind = file.GetMethodBodyInfoInd(method_ind);

        AddFrame(
            func, // We have to pass real value. Undefined won't work.
            file,
            mbi_ind,
            _this,
            argc,
            argv,
            false, // discard_result
            &real_tr.GetStoredScopeStack(),
            &real_tr
            SF_DEBUG_ARG(real_tr.GetVT().GetName(AbsoluteIndex(ind)))
            );
    }
    else
    {
        // Thunk.

        SIMD::IS::PrefetchObj(&real_func.AsThunk());
        const ThunkInfo& thunk = real_func.AsThunk();
        Value result;

        ExecuteThunkUnsafe(thunk, _this, result, argc, argv, true);
    }
}

SF_INLINE
void VM::ExecuteThunkUnsafe(const ThunkInfo& thunk, const Value& _this, Value& result, unsigned argc, const Value* argv, bool result_on_stack)
{
#ifndef SF_AS3_ENABLE_ARGNUM_VALIDATION_IN_TRACER
    // Check number of arguments.
    const unsigned max_arg_num = thunk.GetMaxArgNum();
    // max_arg_num == 1023 means "variable number of arguments".
    if (max_arg_num != 1023 && (argc > max_arg_num || argc < thunk.GetMinArgNum()))
        return ThrowArgumentError(VM::Error(VM::eWrongArgumentCountError, *this SF_DEBUG_ARG(thunk.Name) SF_DEBUG_ARG(thunk.GetMinArgNum()) SF_DEBUG_ARG(thunk.GetMaxArgNum()) SF_DEBUG_ARG(argc)));
#endif

#ifdef SF_FPE_ENABLE
    FPEGuard fpe_guard;
#endif

    // Run method.
    (*thunk.Method)(thunk, *this, _this, result, argc, argv);

    // C++. We need to handle exceptions ...
    if (result_on_stack && !IsException())
        OpStack.PickPushBack(result);
}

SF_INLINE
void VM::ExecuteMethodIndUnsafe(const Value& func, const Value& real_func, const Value& _this, Value& result, unsigned argc, const Value* argv, bool result_on_stack SF_DEBUG_ARG(const SInt32 ind))
{
    const SInt32 method_ind = real_func.GetMethodInd();
    const AS3::Traits& real_tr = real_func.GetTraits();
    SF_ASSERT(real_tr.GetFilePtr());
    VMAbcFile& file = *real_tr.GetFilePtr();
    const SInt32 mbi_ind = file.GetMethodBodyInfoInd(method_ind);

    AddFrame(
        func,
        file,
        mbi_ind,
        _this,
        argc,
        argv,
        false, // discard_result
        &real_tr.GetStoredScopeStack(),
        &real_tr
        SF_DEBUG_ARG(real_tr.GetVT().GetName(AbsoluteIndex(ind)))
        );

    if (!result_on_stack)
        ExecuteAndRetrieveResult(result);
}

void VM::Execute_IgnoreExceptionUnsafe(const Value& func, const Value& _this,
                                       Value& result, unsigned argc, const Value* argv)
{
    ExecuteUnsafe(func, _this, result, argc, argv);
    if (IsException())    
        OutputAndIgnoreException();
}


void VM::Coerce2ReturnType(const Value& value, Value& result)
{
    // Resolve multiname ...
    const CallFrame& cf = GetCurrCallFrame();
    const Abc::Multiname& mn = cf.GetReturnType();
    const ClassTraits::Traits* to = Resolve2ClassTraits(cf.GetFile(), mn);

    if (to)
    {
        if (!to->Coerce(value, result))
        {
            // A TypeError is thrown if return_value cannot be coerced to the expected return type of the
            // executing method.
            return ThrowTypeError(VM::Error(VM::eCheckTypeFailedError, *this
                SF_DEBUG_ARG(value)
                SF_DEBUG_ARG(to->GetName().ToCStr())
                ));
        }
    } else
    {
        //SF_ASSERT2(false, "Couldn't resolve multiname " + AsString(mn));
        return ThrowTypeError(VM::Error(VM::eClassNotFoundError, *this
            SF_DEBUG_ARG(mn.GetName(cf.GetFile().GetConstPool()).ToCStr())
            ));
    }
}

ClassTraits::Traits* VM::GetClassTraits(const ASString& name, const Instances::Namespace& ns)
{
    TClassTraitsCache::ValueType* ptr = ClassTraitsSet.Get(name, ns);

    if (ptr == NULL)
        return NULL;

    return *ptr;
}

ClassTraits::UserDefined& VM::GetUserDefinedTraits(VMAbcFile& file, const Abc::ClassInfo& ci)
{
    const Abc::Multiname& name = ci.GetName(file.GetConstPool());
    const ASString t_name = file.GetInternedString(name.GetNameInd());
    const Instances::Namespace& t_ns = file.GetInternedNamespace(name.GetNamespaceInd());

    TClassTraitsCache::ValueType* ptr = ClassTraitsSet.Get(t_name, t_ns);

    if (ptr == NULL)
    {
        // check for *scaleform extension* packages.
        const ASString& t_uri = t_ns.GetUri();
        const StringDataPtr t_str(t_uri.ToCStr(), t_uri.GetSize());
        const StringDataPtr scaleform_gfx("scaleform.gfx");

        if (t_str.GetSize() >= scaleform_gfx.GetSize() && SFstrncmp(t_str.ToCStr(), scaleform_gfx.ToCStr(), scaleform_gfx.GetSize()) == 0)
        {
            // This is *scaleform.gfx extension* package.
            return const_cast<ClassTraits::UserDefined&>(
                static_cast<const ClassTraits::UserDefined&>(
                    *Resolve2ClassTraits(file, name)
                    )
                );
        }

        SF_ASSERT(false);
    }

    return static_cast<ClassTraits::UserDefined&>(**ptr);
}

void VM::OutputError(const Value& e)
{
    Value r;
    StringManager& sm = GetStringManager();
    ASString errorString = sm.CreateEmptyString();

    // Stack trace is stored in an Exception object. The easiest way to retrieve it is to call
    // the "getStackTrace" method.
    const Multiname prop_name(GetPublicNamespace(), GetStringManager().CreateConstString("getStackTrace"));
    if (!e.IsNullOrUndefined() && AS3::ExecutePropertyUnsafe(*this, prop_name, e, r, 0, NULL))
    {
        if (!r.Convert2String(errorString))
            return;
    }

    if (e.IsNullOrUndefined() || errorString == GetStringManager().GetBuiltin(AS3Builtin_null))
    {
        // It looks like there is no getStackTrace() method.
        if (!e.Convert2String(errorString))
            return;
    }

    UI.Output(FlashUI::Output_Error, errorString.ToCStr());
}

Pickable<Instances::Namespace> VM::MakeNamespace(Abc::NamespaceKind kind,
                                        const ASString& uri, const Value& prefix) const
{
    SF_UNUSED(uri);
    return static_cast<InstanceTraits::Namespace&>(GetClassTraitsNamespace().GetInstanceTraits()).MakeInstance(kind, uri, prefix);
}

Pickable<Instances::Namespace> VM::MakeInternedNamespace(Abc::NamespaceKind kind,
                                               const ASString& uri) const
{
    if (uri.IsEmpty() && kind == Abc::NS_Public)
        return Pickable<Instances::Namespace>(&GetPublicNamespace(), PickValue);

    InstanceTraits::Namespace& nsInstanceTraits = static_cast<InstanceTraits::Namespace&>(GetClassTraitsNamespace().GetInstanceTraits());
    return nsInstanceTraits.MakeInternedInstance(kind, uri, Value::GetUndefined());
}

Pickable<Instances::Namespace> VM::MakeInternedNamespace(Abc::NamespaceKind kind,
                                               const char* name) const
{
    if (!name) name = "";
    return MakeInternedNamespace(kind, GetStringManager().CreateString(name));    
}

Pickable<Instances::Namespace> VM::MakeInternedNamespace(Abc::NamespaceKind kind, const StringDataPtr& uri) const
{
    return MakeInternedNamespace(kind, GetStringManager().CreateString(uri.ToCStr(), uri.GetSize()));    
}

Instances::Namespace& VM::GetInternedNamespace(Abc::NamespaceKind kind,
                                               const ASString& uri) const
{
    if (uri.IsEmpty() && kind == Abc::NS_Public)
        return GetPublicNamespace();

    InstanceTraits::Namespace& nsInstanceTraits = static_cast<InstanceTraits::Namespace&>(GetClassTraitsNamespace().GetInstanceTraits());
    return nsInstanceTraits.GetInternedInstance(kind, uri, Value::GetUndefined());
}

Instances::Namespace& VM::GetInternedNamespace(Abc::NamespaceKind kind,
                                               const char* name) const
{
    if (!name) name = "";
    return GetInternedNamespace(kind, GetStringManager().CreateString(name));    
}

Instances::Namespace& VM::GetInternedNamespace(Abc::NamespaceKind kind, const StringDataPtr& uri) const
{
    return GetInternedNamespace(kind, GetStringManager().CreateString(uri.ToCStr(), uri.GetSize()));    
}

SPtr<VMAbcFile> VM::LoadFile(const Ptr<Abc::File>& file, bool to_execute)
{
    // We need pCurrentFile to be able to initialize InstanceTraits.
    SPtr<VMAbcFile> vmfile(MakePickable(SF_HEAP_NEW_ID(GetMemoryHeap(), StatMV_VM_VMAbcFile_Mem) VMAbcFile(*this, file)));

    if (vmfile->Load(to_execute))
    {
        // Register file.
        //Files.PushBack(vmfile);
        return vmfile;
    }

    return NULL;
}

Class* VM::GetClass(const StringDataPtr& gname)
{
    Class* _class = NULL;

    // This check for empty name slightly improves performance.
    if (!gname.IsEmpty())
    {
        static const StringDataPtr vecPref("Vector.<", 8);

        if (gname.GetSize() > vecPref.GetSize() && gname.GetTrimRight(gname.GetSize() - vecPref.GetSize()) == vecPref)
        {
            SPInt end = gname.FindLastChar('>');
            if (end > 0)
            {
                const StringDataPtr subtype_name(gname.GetTrimLeft(vecPref.GetSize()).GetTrimRight(gname.GetSize() - end));
                Class* subtype_class = GetClass(subtype_name);

                if (subtype_class)
                {
                    const Value subtype_value(subtype_class);
                    _class = &GetClassVector().ApplyTypeArgs(1, &subtype_value);
                }
            }
        }
        else
        {
            // Create a parsed multiname
            const Multiname mn(*this, gname);

            // Check for a Class name.
            const ClassTraits::Traits* ctr = Resolve2ClassTraits(mn);

            if (ctr)
            {
                ctr->InitOnDemand();

                if (!IsException())
                    _class = &ctr->GetInstanceTraits().GetClass();
            }
        }
    }

    return _class;
}

bool VM::GetClassUnsafe(const StringDataPtr& gname, Value& result)
{
    Class* _class = GetClass(gname);

    if (_class)
    {
        result.AssignUnsafe(_class) ;
        return true;
    }

    if (IsException())
        return false;

    ThrowReferenceError(VM::Error(VM::eUndefinedVarError, *this
        SF_DEBUG_ARG(gname.ToCStr())
        ));

    return false;
}

bool VM::Construct(const char* gname, Value& result, unsigned argc, const Value* argv, bool extCall)
{
    const UPInt original_stack_size = CallStack.GetSize();

    // Get class.
    Value value;
    // !!! GetClass() MAY NOT be used here because of initialization on demand.
    if (!GetClassUnsafe(gname, value))
        return false;

    //A TypeError is thrown if object does not implement the [[Construct]] property.

    if (value.IsNullOrUndefined())
    {
        ThrowTypeError(VM::Error(VM::eConvertNullToObjectError, *this));
        return false;
    }

    // Create instance.
    value.GetObject()->Construct(result, argc, argv, extCall);

    if (IsException())
        return false;

    return CallStack.GetSize() > original_stack_size;
}

// Private helper to ConstructBuiltinObject
CheckResult VM::constructBuiltinObject(SPtr<Object> &pobj, const char* gname,
                                unsigned argc, const Value* argv)
{
    Value v;
    Construct(gname, v, argc, argv);

    if (!IsException() && !v.IsNullOrUndefined())
    {
        pobj = v.GetObject();
        return true;
    }        
    pobj = 0;
    if (IsException())
        IgnoreException();
    return false;
}

Traits& VM::GetValueTraits(const Value& v) const
{
    switch (v.GetKind())
    {
    case Value::kUndefined:
        break;
    case Value::kBoolean:
        return GetClassTraitsBoolean().GetInstanceTraits();
    case Value::kInt:
        return GetClassTraitsInt().GetInstanceTraits();
    case Value::kUInt:
        return GetClassTraitsUInt().GetInstanceTraits();
    case Value::kNumber:
        return GetClassTraitsNumber().GetInstanceTraits();
    case Value::kString:
        if (v.GetStringNode())
            return GetClassTraitsString().GetInstanceTraits();
        else
            return GetClassTraitsObject().GetInstanceTraits();
    case Value::kNamespace:
        return GetClassTraitsNamespace().GetInstanceTraits();
    case Value::kFunction:
    case Value::kObject:
    case Value::kClass:
    // ThunkFunction is a real Object. It just wraps a Thunk.
    case Value::kThunkFunction:
        if (v.IsNull())
            return GetClassTraitsObject().GetInstanceTraits();
        else
            return v.GetObject()->GetTraits();
    case Value::kThunk:
    case Value::kThunkClosure:
        return GetClassTraitsFunction().GetThunkTraits();
#if 1 
    // We MAY NOT return different traits here until we fix class Tracer to 
    // return the same Traits for these cases.
    case Value::kVTableInd:
    case Value::kVTableIndClosure:
        return GetClassTraitsFunction().GetVTableTraits();
#else
#if 0
    case Value::kVTableInd:
        {
            const VTable& vt = v.GetVTable();
            const SInt32 ind = v.GetVTableInd();
            const Value& real_func = vt.GetRaw(AbsoluteIndex(ind));

            // VTable stores MethodInd or Thunk.
            if (real_func.GetKind() == Value::kMethodInd)
            {
                // MethodInd.
                const VTable& real_vt = real_func.GetVTable();
                return real_vt.GetTraits();
            }
            else
                // Thunk.
                return GetClassTraitsFunction().GetThunkTraits();
        }
        break;
    case Value::kVTableIndClosure:
        {
            const VTable& vt = v.GetClosure()->GetVT();
            const SInt32 ind = v.GetVTableInd();
            const Value& real_func = vt.GetRaw(AbsoluteIndex(ind));

            // VTable stores MethodInd or Thunk.
            if (real_func.GetKind() == Value::kMethodInd)
            {
                // MethodInd.
                const VTable& real_vt = real_func.GetVTable();
                return real_vt.GetTraits();
            }
            else
                // Thunk.
                return GetClassTraitsFunction().GetThunkTraits();
        }
        break;
#else
    case Value::kVTableInd:
        {
            const VTable& vt = v.GetVTable();
            return vt.GetTraits();
        }
        break;
    case Value::kVTableIndClosure:
        return v.GetClosure()->GetTraits();
#endif
#endif
    case Value::kInstanceTraits:
        return v.GetInstanceTraits();
    case Value::kClassTraits:
        return v.GetClassTraits();
    case Value::kMethodInd:
        break;
    }

    return GetITraitsVoid();
}

const ClassTraits::Traits& VM::GetClassTraits(const Value& v) const
{
    switch(v.GetKind())
    {
    case Value::kBoolean:
        return GetClassTraitsBoolean();
    case Value::kInt:
        return GetClassTraitsInt();
    case Value::kUInt:
        return GetClassTraitsUInt();
    case Value::kNumber:
        return GetClassTraitsNumber();
    case Value::kString:
        if (v.GetStringNode())
            // Not null.
            return GetClassTraitsString();
        else
            // Return ClassTraits::Object for null.
            return GetClassTraitsObject();
    case Value::kClass:
        return v.AsClass().GetClassTraits();
    case Value::kNamespace:
        return GetClassTraitsNamespace();
    case Value::kThunk:
    case Value::kThunkFunction:
    case Value::kFunction:
    case Value::kThunkClosure:
    case Value::kVTableInd:
    case Value::kVTableIndClosure:
        // This should work in case of null.
        return *TraitsFunction;
    case Value::kClassTraits:
        return v.GetClassTraits();
    default:
        break;
    }

    if (v.GetObject())
        return v.GetObject()->GetClass().GetClassTraits();
    else
        // Return ClassTraits::Object for null.
        return GetClassTraitsObject();
}

InstanceTraits::Traits& VM::GetInstanceTraits(const Value& v) const
{
    switch (v.GetKind())
    {
    case Value::kUndefined:
        break;
    case Value::kBoolean:
        return GetClassTraitsBoolean().GetInstanceTraits();
    case Value::kInt:
        return GetClassTraitsInt().GetInstanceTraits();
    case Value::kUInt:
        return GetClassTraitsUInt().GetInstanceTraits();
    case Value::kNumber:
        return GetClassTraitsNumber().GetInstanceTraits();
    case Value::kString:
        if (v.GetStringNode())
            // Not null.
            return GetClassTraitsString().GetInstanceTraits();
        else
            return GetClassTraitsObject().GetInstanceTraits();
    case Value::kNamespace:
        return GetClassTraitsNamespace().GetInstanceTraits();
    case Value::kFunction:
    case Value::kObject:
        // ThunkFunction is a real Object. It just wraps a Thunk.
    case Value::kThunkFunction:
        if (v.IsNull())
            return GetClassTraitsObject().GetInstanceTraits();
        else
            return static_cast<InstanceTraits::Traits&>(v.GetObject()->GetTraits());
    case Value::kClass:
        if (v.IsNull())
            // ??? Object?
            return GetClassTraitsObject().GetInstanceTraits();
        else
            return v.AsClass().GetClassTraits().GetInstanceTraits();
    case Value::kThunk:
    case Value::kThunkClosure:
        return GetClassTraitsFunction().GetThunkTraits();
    case Value::kVTableInd:
    case Value::kVTableIndClosure:
        return GetClassTraitsFunction().GetVTableTraits();
    case Value::kInstanceTraits:
        return v.GetInstanceTraits();
    case Value::kClassTraits:
        {
            const ClassTraits::Traits& ctr = v.GetClassTraits();
            if (ctr.IsValid())
                return ctr.GetInstanceTraits();
        }
    case Value::kMethodInd:
        break;
    }

    return GetITraitsVoid();
}

const Value& VM::GetGlobalObject() const
{
    if (GetCallStack().GetSize() != 0)
    {
        const ScopeStackType* sss = GetCurrCallFrame().GetSavedScope();

        if (sss && !sss->IsEmpty())
            return sss->At(0);

        return GetRegister(AbsoluteIndex(0));
    }
    
    // Do we have a better solution?
    return GetGlobalObjectCPPValue();
}

Value VM::GetDefaultValue(const ClassTraits::Traits& ctr) const
{
    const BuiltinTraitsType tt = ctr.GetTraitsType();

    switch (tt)
    {
    case Traits_Boolean:
        return Value(false);
    case Traits_SInt:
        return Value(SInt32(0));
    case Traits_UInt:
        return Value(UInt32(0));
    case Traits_Number:
        return Value(NumberUtil::NaN());
        // Do not delete code below.
        // !!! We MAY NOT return empty string as a default value.
        // case Traits_String:
        //    return GetStringManager().CreateEmptyString();
    default:
        if (&ctr == &GetClassTraitsClassClass())
            return Value::GetUndefined();
        break;
    }

    return Value::GetNull();
}

Value VM::GetDefaultValue(VMAbcFile& file, const Abc::Multiname& mn)
{
    if (&mn != &file.GetConstPool().GetAnyType())
    {
        // AnyType gets converted to *undefined*.
        const ClassTraits::Traits* ctr = Resolve2ClassTraits(file, mn);

        if (ctr)
            return GetDefaultValue(*ctr);
    }

    return Value::GetUndefined();
}

bool VM::CheckObject(const Value& v)
{
    bool result = true;

    if (v.IsNullOrUndefined())
    {
        ThrowTypeError(VM::Error(v.IsNull() ? VM::eConvertNullToObjectError : VM::eConvertUndefinedToObjectError, *this));
        result = false;
    }

    return result;
}

void VM::RegisterClassInfoTable(const ClassInfo* table[])
{
    GetGlobalObjectCPP().RegisterClassInfoTable(table);
}

void VM::GetStackTraceASString(ASString& result, const char* line_pref) const
{
#ifdef GFX_AS3_VERBOSE
    const CallStackType& cs = GetCallStack();

    for (UPInt i = cs.GetSize(), j = 0; i > 0; --i, ++j)
    {
#ifdef SF_AS3_ENABLE_CALLFRAME_CACHE
        const CallFrame& cf = *cs[i - 1];
#else
        const CallFrame& cf = cs[i - 1];
#endif

        if (j > 0)
            result += "\n";

        result += line_pref;
        result += "at ";
        result += ASString(cf.GetName());
        result += "()";
        if (cf.GetCurrFileInd() != 0)
        {
            result += "[";
            result += cf.GetCurrFileName();
            result += ":";
            result += Scaleform::AsString(cf.GetCurrLineNumber());
            result += "]";
        }
    }
#else
    SF_UNUSED(line_pref);
    result = GetStringManager().GetBuiltin(AS3Builtin_null);
#endif
}

void VM::GetCodeFileName(ASString& result) const
{
    const CallFrame& cf = GetCurrCallFrame();
    const Abc::File& file = cf.GetFile().GetAbcFile();
    result = file.GetSource();
}

#ifdef GFX_AS3_VERBOSE
static
ASString GetThunkName(ASString base, const ThunkInfo& thunk, bool isClosure)
{
    if (!base.IsEmpty())
    {
        if (!base.IsEmpty())
            base += "/";

        if (isClosure && thunk.NamespaceName && *thunk.NamespaceName != 0)
        {
            if (strcmp(thunk.NamespaceName, NS_Vector) != 0)
            {
                if (strcmp(thunk.NamespaceName, NS_AS3) == 0)
                    base += "AS3";
                else if (strcmp(thunk.NamespaceName, NS_flash_proxy) == 0)
                    base += "flash_proxy";
                else
                    base += thunk.NamespaceName;

                base += "::";
            }
        }
    }

    if (isClosure)
        base = "MethodClosure " + base;
    else
        base = "Function " + base;

    base += thunk.Name;
    base += "()";

    return base;
}

static
ASString GetVTableIndName(ASString base, const VTable& vt, SInt32 ind, bool isClosure)
{
    const Value& real_func = vt.GetRaw(AbsoluteIndex(ind));

    // VTable stores MethodInd or Thunk.
    if (real_func.GetKind() == Value::kMethodInd)
    {
        // MethodInd.

        if (isClosure)
            base = "MethodClosure ";
        else
            base = "Function ";

        //return vt.GetTraits().GetQualifiedName() + "::" + vt.GetName(AbsoluteIndex(ind));
        return base + vt.GetName(AbsoluteIndex(ind)) + "()";
    }

    // Thunk.
    return GetThunkName(base, real_func.AsThunk(), isClosure);
}

static
ASString GetNameSkipVectorNS(const Traits& tr)
{
    const InstanceTraits::Traits* itr = NULL;

    if (tr.IsClassTraits())
        itr = &static_cast<const ClassTraits::Traits&>(tr).GetInstanceTraits();
    else
        itr = &static_cast<const InstanceTraits::Traits&>(tr);

    SF_ASSERT(itr);
    if (itr->GetNamespace().GetUri() == NS_Vector)
        return tr.GetName();

    return tr.GetQualifiedName();
}

#endif

ASString VM::describeTypeEx(const Value& value) const
{
    SF_UNUSED1(value);
    StringManager& sm = GetStringManager();
    
#ifdef GFX_AS3_VERBOSE
    switch(value.GetKind())
    {
    case Value::kUndefined:
        return sm.GetBuiltin(AS3Builtin_undefined);
    case Value::kBoolean:
        return sm.GetBuiltin(AS3Builtin_boolean);
    case Value::kInt:
        return sm.CreateConstString("int");
    case Value::kUInt:
        return sm.CreateConstString("uint");
    case Value::kNumber:
        return sm.GetBuiltin(AS3Builtin_number);
    case Value::kString:
        if (value.GetStringNode())
            return sm.GetBuiltin(AS3Builtin_string);
        else
            return sm.GetBuiltin(AS3Builtin_null);
    case Value::kThunk:
        return GetThunkName(sm.GetBuiltin(AS3Builtin_empty_), value.AsThunk(), false);
    case Value::kThunkFunction:
        {
            const Instances::ThunkFunction& tf = value.AsThunkFunction();
            const Traits& otr = tf.GetOriginationTraits();

            return GetThunkName(GetNameSkipVectorNS(otr), tf.GetThunk(), false);
        }
    case Value::kVTableInd:
        return GetVTableIndName(
            sm.GetBuiltin(AS3Builtin_empty_),
            value.GetTraits().GetVT(),
            value.GetVTableInd(),
            false
            );
        break;
    case Value::kVTableIndClosure:
        return GetVTableIndName(
            GetNameSkipVectorNS(value.GetClosure()->GetTraits()),
            value.GetClosure()->GetVT(),
            value.GetVTableInd(),
            true
            );
        break;
    case Value::kFunction:
        {
            const Instances::Function& f = value.AsFunction();
            const Traits& otr = f.GetOriginationTraits();
            
            return GetNameSkipVectorNS(otr) + "::" + f.GetName();
        }
    case Value::kObject:
        if (value.GetObject())
            return GetNameSkipVectorNS(value.GetObject()->GetTraits());
        else
            return sm.GetBuiltin(AS3Builtin_null);
        break; // Just in case.
    case Value::kClass:
        if (value.GetObject())
            return GetNameSkipVectorNS(value.GetObject()->GetTraits()).AppendChar('$');
        else
            return sm.GetBuiltin(AS3Builtin_null);
    case Value::kNamespace:
        {
            const Instances::Namespace& ns = value.AsNamespace();
            ASString result = sm.CreateConstString(AS3::AsString(ns.GetKind()));

            if (!ns.GetUri().IsEmpty())
            {
                result += " ";
                result += ns.GetUri();
            }
            return result;
        }
    case Value::kThunkClosure:
        return GetThunkName(
            GetNameSkipVectorNS(value.GetClosure()->GetTraits()), 
            value.GetThunkFunct(),
            true
            );
    default:
        SF_ASSERT(false);
        break;
    }
#endif

    return sm.GetBuiltin(AS3Builtin_empty_);
}

#ifdef SF_AMP_SERVER
void VM::SetActiveLine(UInt32 lineNumber)
{
    AMP::ViewStats* stats = GetAdvanceStats();
    if (stats != NULL)
    {
        UInt32 activeLine = stats->GetActiveLine();
        if (lineNumber != activeLine)
        {
            // Record time
            UInt64 newTimestamp = Timer::GetRawTicks();
            stats->RecordSourceLineTime(newTimestamp - ActiveLineTimestamp);
            ActiveLineTimestamp = newTimestamp;

            stats->SetActiveLine(lineNumber);
        }    
    }
}

void VM::SetActiveFile(UInt64 fileId)
{
    AMP::ViewStats* stats = GetAdvanceStats();
    if (stats != NULL)
    {
        UInt64 activeFile = stats->GetActiveFile();
        if (fileId != activeFile)
        {
            // Record time
            UInt64 newTimestamp = Timer::GetRawTicks();
            stats->RecordSourceLineTime(newTimestamp - ActiveLineTimestamp);
            ActiveLineTimestamp = newTimestamp;

            stats->SetActiveFile(fileId);
        }    
    }
}
#endif


Classes::Boolean& VM::GetClassBoolean() const
{
    SF_ASSERT(TraitsBoolean.GetPtr());
    return (Classes::Boolean&)TraitsBoolean->GetInstanceTraits().GetClass();
}

InstanceTraits::Traits& VM::GetITraitsBoolean() const
{
    return GetClassTraitsBoolean().GetInstanceTraits();
}

Classes::Number& VM::GetClassNumber() const
{
    SF_ASSERT(TraitsNumber.GetPtr());
    return (Classes::Number&)TraitsNumber->GetInstanceTraits().GetClass();
}

InstanceTraits::Traits& VM::GetITraitsNumber() const
{
    return GetClassTraitsNumber().GetInstanceTraits();
}

Classes::int_& VM::GetClassInt() const
{
    return (Classes::int_&)GetClassTraitsInt().GetInstanceTraits().GetClass();
}

InstanceTraits::Traits& VM::GetITraitsSInt() const
{
    return GetClassTraitsInt().GetInstanceTraits();
}

Classes::uint& VM::GetClassUInt() const
{
    return (Classes::uint&)GetClassTraitsUInt().GetInstanceTraits().GetClass();
}

InstanceTraits::Traits& VM::GetITraitsUInt() const
{
    return GetClassTraitsUInt().GetInstanceTraits();
}

Classes::String& VM::GetClassString() const
{
    return (Classes::String&)GetClassTraitsString().GetInstanceTraits().GetClass();
}

InstanceTraits::Traits& VM::GetITraitsString() const
{
    return GetClassTraitsString().GetInstanceTraits();
}

Classes::Array& VM::GetClassArray() const
{
    return (Classes::Array&)GetClassTraitsArray().GetInstanceTraits().GetClass();
}

InstanceTraits::Traits& VM::GetITraitsArray() const
{
    return GetClassTraitsArray().GetInstanceTraits();
}

Classes::Vector& VM::GetClassVector() const
{
    return (Classes::Vector&)GetClassTraitsVector().GetInstanceTraits().GetClass();
}

Classes::Vector_int& VM::GetClassVectorSInt() const
{
    return (Classes::Vector_int&)GetClassTraitsVectorSInt().GetInstanceTraits().GetClass();
}

InstanceTraits::Traits& VM::GetITraitsVectorSInt() const
{
    return GetClassTraitsVectorSInt().GetInstanceTraits();
}

Classes::Vector_uint& VM::GetClassVectorUInt() const
{
    return (Classes::Vector_uint&)GetClassTraitsVectorUInt().GetInstanceTraits().GetClass();
}

InstanceTraits::Traits& VM::GetITraitsVectorUInt() const
{
    return GetClassTraitsVectorUInt().GetInstanceTraits();
}

Classes::Vector_double& VM::GetClassVectorNumber() const
{
    return (Classes::Vector_double&)GetClassTraitsVectorNumber().GetInstanceTraits().GetClass();
}

InstanceTraits::Traits& VM::GetITraitsVectorNumber() const
{
    return GetClassTraitsVectorNumber().GetInstanceTraits();
}

Classes::Vector_String& VM::GetClassVectorString() const
{
    return (Classes::Vector_String&)GetClassTraitsVectorString().GetInstanceTraits().GetClass();
}

InstanceTraits::Traits& VM::GetITraitsVectorString() const
{
    return GetClassTraitsVectorString().GetInstanceTraits();
}

#ifdef SF_ENABLE_XML
Classes::QName& VM::GetClassQName() const
{
    SF_ASSERT(TraitsQName.GetPtr());
    return (Classes::QName&)TraitsQName->GetInstanceTraits().GetClass();
}

Classes::XML& VM::GetClassXML() const
{
    SF_ASSERT(TraitsXML.GetPtr());
    return (Classes::XML&)TraitsXML->GetInstanceTraits().GetClass();
}

InstanceTraits::Traits& VM::GetITraitsXML() const
{
    return GetClassTraitsXML().GetInstanceTraits();
}

Classes::XMLList& VM::GetClassXMLList() const
{
    SF_ASSERT(TraitsXMLList.GetPtr());
    return (Classes::XMLList&)TraitsXMLList->GetInstanceTraits().GetClass();
}

InstanceTraits::Traits& VM::GetITraitsXMLList() const
{
    return GetClassTraitsXMLList().GetInstanceTraits();
}
#endif

void VM::ThrowErrorInternal(const Error& e, const ClassInfo& ci)
{
    const ClassTraits::Traits* ctr = Resolve2ClassTraits(
        GetStringManager().CreateConstString(ci.Name),
        //GetPublicNamespace()
        GetInternedNamespace(Abc::NS_Public, ci.PkgName)
        );

    SF_ASSERT(ctr);

    Value obj;
    InstanceTraits::Traits& itr = ctr->GetInstanceTraits();
    itr.MakeObject(obj, itr);
    const Value argv[2] = {Value(e.GetMessage()), Value((SInt32)e.GetErrorID())};
    obj.GetObject()->AS3Constructor(2, argv);
    Throw(obj);
}

void VM::ThrowError(const Error& e)
{
    ThrowErrorInternal(e, ErrorCI);
}

void VM::ThrowEvalError(const Error& e)
{
    ThrowErrorInternal(e, EvalErrorCI);
}

void VM::ThrowRangeError(const Error& e)
{
    ThrowErrorInternal(e, RangeErrorCI);
}

void VM::ThrowReferenceError(const Error& e)
{
    ThrowErrorInternal(e, ReferenceErrorCI);
}

void VM::ThrowSecurityError(const Error& e)
{
    ThrowErrorInternal(e, SecurityErrorCI);
}

void VM::ThrowSyntaxError(const Error& e)
{
    ThrowErrorInternal(e, SyntaxErrorCI);
}

void VM::ThrowTypeError(const Error& e)
{
    ThrowErrorInternal(e, TypeErrorCI);
}

void VM::ThrowURIError(const Error& e)
{
    ThrowErrorInternal(e, URIErrorCI);
}

void VM::ThrowVerifyError(const Error& e)
{
    ThrowErrorInternal(e, VerifyErrorCI);
}

void VM::ThrowUninitializedError(const Error& e)
{
    ThrowErrorInternal(e, UninitializedErrorCI);
}

void VM::ThrowArgumentError(const Error& e)
{
    ThrowErrorInternal(e, ArgumentErrorCI);
}

void VM::ThrowMemoryError(const Error& e)
{
    ThrowErrorInternal(e, MemoryErrorCI);
}

///////////////////////////////////////////////////////////////////////////
#ifdef GFX_AS3_VERBOSE
VM::Error::Error(VM::ErrorID id, VM& vm)
: ID(id), Message(vm.GetStringManager().CreateEmptyString())
{
    String fullMsg;
    const int ind = (int)id;

    const char* builtin_msg = GetErrorMsg(ind);
    Scaleform::Format(fullMsg, "Error #{0}: {1}", ind, builtin_msg);

    Message = vm.GetStringManager().CreateString(fullMsg);
}

VM::Error::Error(VM::ErrorID id, VM& vm, int arg1)
: ID(id), Message(vm.GetStringManager().CreateEmptyString())
{
    String fullMsg;
    String tmpMsg;
    const int ind = (int)id;

    const char* builtin_msg = GetErrorMsg(ind);

    Format(tmpMsg, builtin_msg, arg1);
    Format(fullMsg, "Error #{0}: {1}", ind, tmpMsg);

    Message = vm.GetStringManager().CreateString(fullMsg);
}

VM::Error::Error(VM::ErrorID id, VM& vm, const char* arg1)
: ID(id), Message(vm.GetStringManager().CreateEmptyString())
{
    String fullMsg;
    String tmpMsg;
    const int ind = (int)id;

    const char* builtin_msg = GetErrorMsg(ind);

    Format(tmpMsg, builtin_msg, arg1);
    Format(fullMsg, "Error #{0}: {1}", ind, tmpMsg);

    Message = vm.GetStringManager().CreateString(fullMsg);
}

VM::Error::Error(VM::ErrorID id, VM& vm, const Value& arg1)
: ID(id), Message(vm.GetStringManager().CreateEmptyString())
{
    String fullMsg;
    String tmpMsg;
    const int ind = (int)id;
    StringManager& sm = vm.GetStringManager();

    ASString s1 = sm.CreateEmptyString();
    arg1.Convert2String(s1).DoNotCheck();

    const char* builtin_msg = GetErrorMsg(ind);

    Format(tmpMsg, builtin_msg, s1.ToCStr());
    Format(fullMsg, "Error #{0}: {1}", ind, tmpMsg);

    Message = vm.GetStringManager().CreateString(fullMsg);
}

VM::Error::Error(VM::ErrorID id, VM& vm, int arg1, int arg2)
: ID(id), Message(vm.GetStringManager().CreateEmptyString())
{
    String fullMsg;
    String tmpMsg;
    const int ind = (int)id;

    const char* builtin_msg = GetErrorMsg(ind);

    Format(tmpMsg, builtin_msg, arg1, arg2);
    Format(fullMsg, "Error #{0}: {1}", ind, tmpMsg);

    Message = vm.GetStringManager().CreateString(fullMsg);
}

VM::Error::Error(VM::ErrorID id, VM& vm, const char* arg1, const char* arg2)
: ID(id), Message(vm.GetStringManager().CreateEmptyString())
{
    String fullMsg;
    String tmpMsg;
    const int ind = (int)id;

    const char* builtin_msg = GetErrorMsg(ind);

    Format(tmpMsg, builtin_msg, arg1, arg2);
    Format(fullMsg, "Error #{0}: {1}", ind, tmpMsg);

    Message = vm.GetStringManager().CreateString(fullMsg);
}

VM::Error::Error(VM::ErrorID id, VM& vm, const Value& arg1, const Value& arg2)
: ID(id), Message(vm.GetStringManager().CreateEmptyString())
{
    String fullMsg;
    String tmpMsg;
    const int ind = (int)id;

    StringManager& sm = vm.GetStringManager();

    ASString s1 = sm.CreateEmptyString();
    arg1.Convert2String(s1).DoNotCheck();

    ASString s2 = sm.CreateEmptyString();
    arg2.Convert2String(s2).DoNotCheck();

    const char* builtin_msg = GetErrorMsg(ind);

    Format(tmpMsg, builtin_msg, s1.ToCStr(), s2.ToCStr());
    Format(fullMsg, "Error #{0}: {1}", ind, tmpMsg);

    Message = vm.GetStringManager().CreateString(fullMsg);
}

VM::Error::Error(VM::ErrorID id, VM& vm, const Value& arg1, const char* arg2)
: ID(id), Message(vm.GetStringManager().CreateEmptyString())
{
    String fullMsg;
    String tmpMsg;
    const int ind = (int)id;
    StringManager& sm = vm.GetStringManager();

    ASString s1 = sm.CreateEmptyString();
    arg1.Convert2String(s1).DoNotCheck();

    const char* builtin_msg = GetErrorMsg(ind);

    Format(tmpMsg, builtin_msg, s1.ToCStr(), arg2);
    Format(fullMsg, "Error #{0}: {1}", ind, tmpMsg);

    Message = vm.GetStringManager().CreateString(fullMsg);
}

VM::Error::Error(VM::ErrorID id, VM& vm, const char* arg1, const Value& arg2)
: ID(id), Message(vm.GetStringManager().CreateEmptyString())
{
    String fullMsg;
    String tmpMsg;
    const int ind = (int)id;
    StringManager& sm = vm.GetStringManager();

    ASString s2 = sm.CreateEmptyString();
    arg2.Convert2String(s2).DoNotCheck();

    const char* builtin_msg = GetErrorMsg(ind);

    Format(tmpMsg, builtin_msg, arg1, s2.ToCStr());
    Format(fullMsg, "Error #{0}: {1}", ind, tmpMsg);

    Message = vm.GetStringManager().CreateString(fullMsg);
}

VM::Error::Error(VM::ErrorID id, VM& vm, const char* arg1, int arg2, int arg3, int arg4)
: ID(id), Message(vm.GetStringManager().CreateEmptyString())
{
    String fullMsg;
    String tmpMsg;
    const int ind = (int)id;

    const char* builtin_msg = GetErrorMsg(ind);

    Format(tmpMsg, builtin_msg, arg1, arg2, arg3, arg4);
    Format(fullMsg, "Error #{0}: {1}", ind, tmpMsg);

    Message = vm.GetStringManager().CreateString(fullMsg);
}

#else

VM::Error::Error(VM::ErrorID id, VM& vm)
: ID(id), Message(vm.GetStringManager().CreateEmptyString())
{
    String fullMsg;
    const int ind = (int)id;

    Scaleform::Format(fullMsg, "Error #{0}", ind);

    Message = vm.GetStringManager().CreateString(fullMsg);
}

#endif

///////////////////////////////////////////////////////////////////////////
void ThunkInfo::EmptyFunc(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv)
{
#if 0
    SF_UNUSED5(ti, _this, result, argc, argv);
    WARN_NOT_IMPLEMENTED_STATIC("ThunkInfo::EmptyFunc()");
#else
    SF_UNUSED4(_this, result, argc, argv);
    String str("The method ");
    if (ti.NamespaceName)
    {
        str += ti.NamespaceName;
        str += "::";
    }
    if (ti.Name)
    {
        str += ti.Name;
        str += "()";
    }
    str += " is not implemented\n";

    vm.GetUI().Output(FlashUI::Output_Warning, str.ToCStr());
#endif
}

///////////////////////////////////////////////////////////////////////////
// We keep implementation here because of Array.
CheckResult SetProperty(VM& vm, const Value& _this, const Multiname& prop_name, const Value& value)
{
    /* For maniacs
    if (_this.IsNullOrUndefined())
    {
        vm.ThrowTypeError(VM::eConvertUndefinedToObjectError);
        return false;
    }
    */

    const Traits& tr = vm.GetValueTraits(_this);
    if (tr.IsArrayLike())
        return _this.GetObject()->SetProperty(prop_name, value);

    // Find a property.
    // Find + Set shouldn't mutate a prototype object.
    // Search in own properties only. Ignore prototype.
    PropRef prop;
    AS3::FindObjProperty(prop, vm, _this, prop_name, FindSet);

    if (prop)
        return prop.SetSlotValue(vm, value);
    else if (_this.IsObject())
    {
        Object& obj = *_this.GetObject();

        // Dynamic properties can only be assigned to public namespace.
        // TBD: Add Multiname::AsValidDynamicName()?. Empty names shouldn't be allowed...
        if (obj.IsDynamic() &&
            prop_name.ContainsNamespace(vm.GetPublicNamespace()))
        {
            obj.AddDynamicSlotValuePair(prop_name.GetName(), value);
            return true;
        }
    }

    // A ReferenceError is thrown if the property is unresolved and obj is not dynamic.
    vm.ThrowReferenceError(VM::Error(VM::eWriteSealedError, vm
        SF_DEBUG_ARG(prop_name.GetName())
        SF_DEBUG_ARG(tr.GetName().ToCStr())
        ));

    return false;
}

CheckResult GetPropertyUnsafe(VM& vm, const Value& _this, const Multiname& prop_name, Value& value)
{
    /* For maniacs
    if (_this.IsNullOrUndefined())
    {
        vm.ThrowTypeError(VM::eConvertUndefinedToObjectError);
        return false;
    }
    */

    const Traits& tr = vm.GetValueTraits(_this);
    if (tr.IsArrayLike())
        return _this.GetObject()->GetProperty(prop_name, value);

    // Find a property.
    PropRef prop;

    FindObjProperty(prop, vm, _this, prop_name);

    if (prop)
        return prop.GetSlotValueUnsafe(vm, value);

    return false;
}

///////////////////////////////////////////////////////////////////////////
// Keep it here for the time being.

CheckResult Object::SetProperty(const Multiname& prop_name, const Value& value)
{
    // Find a property.

    VM& vm = GetVM();

    // Find + Set shouldn't mutate a prototype object.
    PropRef prop;

    AS3::FindObjProperty(prop, GetVM(), Value(this), prop_name, FindSet);

    if (prop)
        return prop.SetSlotValue(vm, value);
    else
    {
        Object& obj = *this;
        
        // Dynamic properties can only be assigned to public namespace.
        // TBD: Add Multiname::AsValidDynamicName()?. Empty names shouldn't be allowed...
        if (obj.IsDynamic() &&
            prop_name.ContainsNamespace(vm.GetPublicNamespace()))
        {
            obj.AddDynamicSlotValuePair(prop_name.GetName(), value);
            return true;
        }
    }

    // A ReferenceError is thrown if the property is unresolved and obj is not dynamic.
    vm.ThrowReferenceError(VM::Error(VM::eWriteSealedError, vm
        SF_DEBUG_ARG(prop_name.GetName())
        SF_DEBUG_ARG(GetTraits().GetName().ToCStr())
        ));

    return false;
}

CheckResult Object::GetProperty(const Multiname& prop_name, Value& value)
{
    VM& vm = GetVM();

    // Find a property.
    PropRef prop;

    AS3::FindObjProperty(prop, vm, Value(this), prop_name);

    if (prop)
    {
        Value v;

        if (prop.GetSlotValueUnsafe(vm, v))
        {
            value.Swap(v);
            return true;
        }
    }

    return false;
}

void Object::GetDynamicProperty(AbsoluteIndex ind, Value& value)
{
    const DynAttrsType::ConstIterator bit = DynAttrs.Begin();
    DynAttrsType::ConstIterator it(bit.GetContainer(), ind .Get());

    value.Assign(it->Second);
}

CheckResult Object::DeleteProperty(const Multiname& prop_name)
{
    if (IsDynamic())
        return DeleteDynamicSlotValuePair(prop_name);

    return false;
}


#if defined(SF_FPE_ENABLE)
FPEGuard::FPEGuard()
{
#if defined(SF_OS_WIN32) || defined(SF_OS_XBOX360)
#if defined(SF_MSVC_SAFESTRING)
    unsigned c;
    _controlfp_s(&c, _DN_FLUSH, _MCW_DN); // flush abnormal results and operands to zero

    // Reset any pending exceptions
    _fpreset();

    // Disable all exceptions and store previous state.
    _controlfp_s(&State, _EM_INEXACT | _EM_UNDERFLOW | _EM_OVERFLOW | _EM_ZERODIVIDE | _EM_INVALID, _MCW_EM);
#else
    _controlfp(_DN_FLUSH, _MCW_DN); // flush abnormal results and operands to zero

    // Reset any pending exceptions
    _fpreset();

    // Get current state.
    State = _controlfp(0, 0);
    // Disable all exceptions and store previous state.
    _controlfp(_EM_INEXACT | _EM_UNDERFLOW | _EM_OVERFLOW | _EM_ZERODIVIDE | _EM_INVALID, _MCW_EM);
#endif
#endif
}

FPEGuard::~FPEGuard()
{
#if defined(SF_OS_WIN32) || defined(SF_OS_XBOX360)
#if defined(SF_MSVC_SAFESTRING)
    unsigned c;
    _controlfp_s(&c, _DN_FLUSH, _MCW_DN); // flush abnormal results and operands to zero

    // Reset any pending exceptions
    _fpreset();

    // Disable all exceptions and store previous state.
    _controlfp_s(&c, State, _MCW_EM);
#else
    _controlfp(_DN_FLUSH, _MCW_DN); // flush abnormal results and operands to zero

    // Reset any pending exceptions
    _fpreset();

    // Disable all exceptions and store previous state.
    _controlfp(State, _MCW_EM);
#endif
#endif
}

#endif

}}} // namespace Scaleform { namespace GFx { namespace AS3 {

