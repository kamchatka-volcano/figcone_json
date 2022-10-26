#ifndef FIGCONE_JSON_PARSER_H
#define FIGCONE_JSON_PARSER_H

#include <figcone_tree/tree.h>
#include <figcone_tree/iparser.h>
#include <vector>
#include <string>

namespace figcone::json {
class Parser : public IParser{
public:
    TreeNode parse(std::istream& stream) override;
};

}

#endif //FIGCONE_JSON_PARSER_H