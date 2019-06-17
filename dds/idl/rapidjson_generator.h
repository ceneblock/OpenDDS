/*
 *
 *
 * Distributed under the OpenDDS License.
 * See: http://www.opendds.org/license.html
 */

#ifndef rapidjson_generator_H
#define rapidjson_generator_H

#include "dds_generator.h"

class rapidjson_generator : public dds_generator {

public:
  rapidjson_generator() {}

private:
  bool gen_enum(AST_Enum*, UTL_ScopedName* name,
                const std::vector<AST_EnumVal*>& contents, const char* repoid);

  bool gen_struct(AST_Structure*, UTL_ScopedName* name,
                  const std::vector<AST_Field*>& fields,
                  AST_Type::SIZE_TYPE size, const char* repoid);

  bool gen_typedef(AST_Typedef*, UTL_ScopedName* name, AST_Type* type,
                   const char* repoid);

  bool gen_array(AST_Array*, UTL_ScopedName* name, AST_Type* type,
                   const char* repoid);

  bool gen_union(AST_Union*, UTL_ScopedName* name,
                 const std::vector<AST_UnionBranch*>& branches,
                 AST_Type* type, const char* repoid);

  void gen_includes();
};

#endif
