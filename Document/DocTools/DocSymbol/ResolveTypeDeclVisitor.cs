﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DocSymbol
{
    class ResolveTypeDeclVisitor : TypeDecl.IVisitor
    {
        public SymbolDecl Symbol { get; set; }
        public List<string> Errors { get; set; }
        public string Result { get; set; }

        public void Visit(RefTypeDecl decl)
        {
            switch (decl.Name)
            {
                case "__int8":
                case "__int16":
                case "__int32":
                case "__int64":
                case "char":
                case "wchar_t":
                case "bool":
                case "float":
                case "double":
                    break;
                default:
                    throw new NotImplementedException();
            }
        }

        public void Visit(SubTypeDecl decl)
        {
            decl.Parent.Resolve(this.Symbol, this.Errors);
            throw new NotImplementedException();
        }

        public void Visit(DecorateTypeDecl decl)
        {
            decl.Element.Resolve(this.Symbol, this.Errors);
        }

        public void Visit(ArrayTypeDecl decl)
        {
            decl.Element.Resolve(this.Symbol, this.Errors);
        }

        public void Visit(FunctionTypeDecl decl)
        {
            decl.ReturnType.Resolve(this.Symbol, this.Errors);
            foreach (var type in decl.Parameters)
            {
                type.Resolve(this.Errors);
            }
        }

        public void Visit(ClassMemberTypeDecl decl)
        {
            decl.Element.Resolve(this.Symbol, this.Errors);
            decl.ClassType.Resolve(this.Symbol, this.Errors);
        }

        public void Visit(GenericTypeDecl decl)
        {
            decl.Element.Resolve(this.Symbol, this.Errors);
            foreach (var type in decl.TypeArguments)
            {
                type.Resolve(this.Symbol, this.Errors);
            }
        }

        public void Visit(DeclTypeDecl decl)
        {
        }

        public void Visit(VariadicArgumentTypeDecl decl)
        {
            decl.Element.Resolve(this.Symbol, this.Errors);
        }

        public void Visit(ConstantTypeDecl decl)
        {
        }
    }

    class ResolveSymbolDeclVisitor : SymbolDecl.IVisitor
    {
        public List<string> Errors { get; set; }

        public void Visit(GlobalDecl decl)
        {
        }

        public void Visit(NamespaceDecl decl)
        {
        }

        public void Visit(UsingNamespaceDecl decl)
        {
        }

        public void Visit(TemplateDecl decl)
        {
            if (decl.Specialization != null)
            {
                foreach (var type in decl.Specialization)
                {
                    type.Resolve(decl, this.Errors);
                }
            }
        }

        public void Visit(BaseTypeDecl decl)
        {
        }

        public void Visit(ClassDecl decl)
        {
            var templateDecl = decl.Parent as TemplateDecl;
            if (templateDecl != null)
            {
                Visit(templateDecl);
            }

            foreach (var baseType in decl.BaseTypes)
            {
                baseType.Type.Resolve(decl, this.Errors);
            }
        }

        public void Visit(VarDecl decl)
        {
            decl.Type.Resolve(decl, this.Errors);
        }

        public void Visit(FuncDecl decl)
        {
            var templateDecl = decl.Parent as TemplateDecl;
            if (templateDecl != null)
            {
                Visit(templateDecl);
            }

            decl.Type.Resolve(decl, this.Errors);
        }

        public void Visit(GroupedFieldDecl decl)
        {
        }

        public void Visit(EnumItemDecl decl)
        {
        }

        public void Visit(EnumDecl decl)
        {
        }

        public void Visit(TypedefDecl decl)
        {
            var templateDecl = decl.Parent as TemplateDecl;
            if (templateDecl != null)
            {
                Visit(templateDecl);
            }

            decl.Type.Resolve(decl, this.Errors);
        }
    }
}