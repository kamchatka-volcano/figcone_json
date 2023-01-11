#ifndef FIGCONE_JSON_PARSER_H
#define FIGCONE_JSON_PARSER_H

#include <figcone_tree/iparser.h>
#include <figcone_tree/tree.h>
#include <string>
#include <vector>

namespace figcone::json {
class Parser : public IParser {
public:
    TreeNode parse(std::istream& stream) override;
};

} //namespace figcone::json

#endif //FIGCONE_JSON_PARSER_H