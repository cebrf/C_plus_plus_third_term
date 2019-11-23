#include <string>
#include <vector>

class FormatVisitor : public BaseVisitor {
 public:
    void Visit(const BaseNode* node) override {
        node->Visit(this);
    }

    void Visit(const ClassDeclarationNode* node) override {
        formattedCode.push_back(indent + "class "
            + node->ClassName() + " {");
        
        if (!node->PublicFields().empty()) {
            formattedCode.push_back(indent + "  public:");
            indent += "    ";
            for (int i = 0; i < node->PublicFields().size(); i++) {
                node->PublicFields()[i]->Visit(this);
                formattedCode[formattedCode.size() - 1] += ";";
            }
            indent = indent.substr(0, indent.size() - 4);
        }

        if (!node->ProtectedFields().empty()) {
            formattedCode.push_back("");
            formattedCode.push_back(indent + "  protected:");
            indent += "    ";
            for (int i = 0; i < node->ProtectedFields().size(); i++) {
                node->ProtectedFields()[i]->Visit(this);
                formattedCode[formattedCode.size() - 1] += ";";
            }
            indent = indent.substr(0, indent.size() - 4);
        }

        if (!node->PrivateFields().empty()) {
            formattedCode.push_back("");
            formattedCode.push_back(indent + "  private:");
            indent += "    ";
            for (int i = 0; i < node->PrivateFields().size(); i++) {
                node->PrivateFields()[i]->Visit(this);
                formattedCode[formattedCode.size() - 1] += ";";
            }
            indent = indent.substr(0, indent.size() - 4);
        }
        formattedCode.push_back(indent + "}");
        if (indent == "") {
            formattedCode[formattedCode.size() - 1] += ";";
        }
    }
    void Visit(const VarDeclarationNode* node) override {
        formattedCode.push_back(indent + node->TypeName()
            + " " + node->VarName());
    }
    void Visit(const MethodDeclarationNode* node) override {
        formattedCode.push_back(indent + node->ReturnTypeName()
            + " " + node->MethodName() + "(");
        for (int i = 0; i < static_cast<int>(node->Arguments().size()); i++) {
            Visit(node->Arguments()[i]);
            formattedCode[formattedCode.size() - 2] +=
                formattedCode[formattedCode.size() - 1].substr(indent.size(),
                    formattedCode[formattedCode.size() - 1].size()
                    - indent.size());
            if (i < node->Arguments().size() - 1) {
                formattedCode[formattedCode.size() - 2] += ", ";
            }
            formattedCode.pop_back();
        }
        formattedCode[formattedCode.size() - 1] += ")";
    }



    const std::vector<std::string>& GetFormattedCode() const {
        for (int i = 0; i < formattedCode.size(); i++) {
            std::cout << formattedCode[i] << '\n';
        }
        return formattedCode;
    }
protected:
    std::string indent = "";
    std::vector<std::string> formattedCode;
};
