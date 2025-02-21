// gameswf_abc.h	-- Vitaly Alexeev <tishka92@yahoo.com>	2008

// This source code has been donated to the Public Domain.  Do
// whatever you want with it.

// do_abc tag reader

#ifndef GAMESWF_ABC_H
#define GAMESWF_ABC_H

#include "gameswf/gameswf_types.h"
#include "gameswf/gameswf_avm2.h"

namespace gameswf
{

	struct abc_def;
	struct as_function;
	struct movie_definition_sub;

	struct multiname
	{
		enum kind
		{
			CONSTANT_UNDEFINED = 0,
			CONSTANT_QName = 0x07,
			CONSTANT_QNameA = 0x0D,
			CONSTANT_RTQName = 0x0F,
			CONSTANT_RTQNameA = 0x10,
			CONSTANT_RTQNameL = 0x11,
			CONSTANT_RTQNameLA = 0x12,
			CONSTANT_Multiname = 0x09,
			CONSTANT_MultinameA = 0x0E,
			CONSTANT_MultinameL = 0x1B,
			CONSTANT_MultinameLA = 0x1C
		};

		int m_kind;
		int m_flags;
		int m_ns;
		int m_ns_set;
		int m_name;

		multiname() :
			m_kind(CONSTANT_UNDEFINED),
			m_flags(0),
			m_ns(0),
			m_name(0)
		{
		}

		inline bool is_qname() const
		{
			return m_kind == CONSTANT_QName;
		}
	};

	struct namespac
	{
		enum kind
		{
			CONSTANT_Undefined = 0,
			CONSTANT_Namespace = 0x08,
			CONSTANT_PackageNamespace = 0x16,
			CONSTANT_PackageInternalNs = 0x17,
			CONSTANT_ProtectedNamespace = 0x18,
			CONSTANT_ExplicitNamespace = 0x19,
			CONSTANT_StaticProtectedNs = 0x1A,
			CONSTANT_PrivateNs = 0x05
		};

		kind m_kind;
		int	m_name;

		namespac() :
			m_kind(CONSTANT_Undefined),
			m_name(0)
		{
		}

	};

	struct metadata_info : public ref_counted
	{
		void	read(stream* in, abc_def* abc);
	};


	//
	// instance_info
	//
	struct instance_info : public ref_counted
	{

		enum flags
		{
			CONSTANT_ClassSealed = 0x01,
			CONSTANT_ClassFinal = 0x02,
			CONSTANT_ClassInterface = 0x04,
			CONSTANT_ClassProtectedNs = 0x08
		};

		int m_name;
		int m_super_name;
		Uint8 m_flags;
		int m_protectedNs;
		array<int> m_interface;
		int m_iinit;
		array< smart_ptr<traits_info> > m_trait;

		instance_info() :
			m_name(0),
			m_super_name(0),
			m_flags(0),
			m_protectedNs(0),
			m_iinit(0)
		{
		}

		void	read(stream* in, abc_def* abc);
	};

	struct class_info : public ref_counted
	{
		int m_cinit;
		array< smart_ptr<traits_info> > m_trait;

		void	read(stream* in, abc_def* abc);
	};

	struct script_info : public ref_counted
	{
		int m_init;
		array< smart_ptr<traits_info> > m_trait;

		void	read(stream* in, abc_def* abc);
	};

	struct abc_def : public ref_counted
	{
		// constant pool
		array<int> m_integer;
		array<Uint32> m_uinteger;
		array<double> m_double;
		array<tu_string> m_string;
		array<namespac> m_namespace;
		array< array<int> > m_ns_set;
		array<multiname> m_multiname;

//		array< smart_ptr<method_info> > m_method;
		array< smart_ptr<as_3_function> > m_method;
		array< smart_ptr<metadata_info> > m_metadata;
		array< smart_ptr<instance_info> > m_instance;
		array< smart_ptr<class_info> > m_class;
		array< smart_ptr<script_info> > m_script;

		inline const char* get_string(int index) const
		{
			return m_string[index].c_str(); 
		}

		inline int get_integer(int index) const
		{
			return m_integer[index]; 
		}

		inline double get_double(int index) const
		{
			return m_double[index]; 
		}

		inline const char* get_namespace(int index) const
		{
			return get_string(m_namespace[index].m_name); 
		}

		inline const char* get_multiname(int index) const
		{
			return get_string(m_multiname[index].m_name); 
		}

		abc_def(player* player);
		virtual ~abc_def();

		void	read(stream* in, movie_definition_sub* m);
		void	read_cpool(stream* in);

		// get class constructor
		as_function* get_class_constructor(tu_string& name) const;

		instance_info* find_instance(const tu_string& class_name) const;
	};
}


#endif // GAMESWF_ABC_H
