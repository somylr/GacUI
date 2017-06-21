#include "GuiDocumentEditor.h"

namespace vl
{
	namespace presentation
	{
		using namespace collections;
		using namespace document_editor;

/***********************************************************************
Clear all runs that have an empty length
***********************************************************************/

		namespace document_operation_visitors
		{
			class ClearRunVisitor : public Object, public DocumentRun::IVisitor
			{
			public:
				vint							start;

				ClearRunVisitor()
					:start(0)
				{
				}

				void VisitContainer(DocumentContainerRun* run)
				{
					for (vint i = run->runs.Count() - 1; i >= 0; i--)
					{
						vint oldStart = start;
						run->runs[i]->Accept(this);
						if (oldStart == start)
						{
							run->runs.RemoveAt(i);
						}
					}
				}

				void VisitContent(DocumentContentRun* run)
				{
					start += run->GetRepresentationText().Length();
				}

				void Visit(DocumentTextRun* run)override
				{
					VisitContent(run);
				}

				void Visit(DocumentStylePropertiesRun* run)override
				{
					VisitContainer(run);
				}

				void Visit(DocumentStyleApplicationRun* run)override
				{
					VisitContainer(run);
				}

				void Visit(DocumentHyperlinkRun* run)override
				{
					VisitContainer(run);
				}

				void Visit(DocumentImageRun* run)override
				{
					VisitContent(run);
				}

				void Visit(DocumentEmbeddedObjectRun* run)override
				{
					VisitContent(run);
				}

				void Visit(DocumentParagraphRun* run)override
				{
					VisitContainer(run);
				}
			};
		}
		using namespace document_operation_visitors;

/***********************************************************************
Ensure DocumentStylePropertiesRun doesn't have a child which is another DocumentStylePropertiesRun
Remove DocumentStylePropertiesRun's property if it set a value but doesn't change the output
Remove DocumentStylePropertiesRun if it is empty or contains no text run
***********************************************************************/

		namespace document_operation_visitors
		{
			class CompressStyleRunVisitor : public Object, public DocumentRun::IVisitor
			{
			public:
				DocumentModel*							model;
				List<DocumentModel::ResolvedStyle>		resolvedStyles;
				List<Ptr<DocumentRun>>					replacedRuns;

				CompressStyleRunVisitor(DocumentModel* _model)
					:model(_model)
				{
					DocumentModel::ResolvedStyle resolvedStyle;
					resolvedStyle = model->GetStyle(DocumentModel::DefaultStyleName, resolvedStyle);
					resolvedStyles.Add(resolvedStyle);
				}

				const DocumentModel::ResolvedStyle& GetCurrentResolvedStyle()
				{
					return resolvedStyles[resolvedStyles.Count() - 1];
				}

				void VisitContainer(DocumentContainerRun* run)
				{
					for (vint i = 0; i < run->runs.Count(); i++)
					{
						Ptr<DocumentRun> subRun = run->runs[i];
						replacedRuns.Clear();
						subRun->Accept(this);
						if (replacedRuns.Count() > 0)
						{
							run->runs.RemoveAt(i);
							for (vint j = 0; j < replacedRuns.Count(); j++)
							{
								run->runs.Insert(i + j, replacedRuns[j]);
							}
							i--;
						}
					}
				}

				void Visit(DocumentTextRun* run)override
				{
				}

				void Visit(DocumentStylePropertiesRun* run)override
				{
					{
						bool onlyImageOrObject = true;
						FOREACH(Ptr<DocumentRun>, subRun, run->runs)
						{
							if (!subRun.Cast<DocumentImageRun>() && !subRun.Cast<DocumentEmbeddedObjectRun>())
							{
								onlyImageOrObject = false;
								break;
							}
						}

						if (onlyImageOrObject)
						{
							CopyFrom(replacedRuns, run->runs);
							return;
						}
					}

					const DocumentModel::ResolvedStyle& currentResolvedStyle = GetCurrentResolvedStyle();
					DocumentModel::ResolvedStyle resolvedStyle = model->GetStyle(run->style, currentResolvedStyle);

					if (currentResolvedStyle.style.fontFamily			== resolvedStyle.style.fontFamily)			run->style->face =				Nullable<WString>();
					if (currentResolvedStyle.style.size					== resolvedStyle.style.size)				run->style->size =				Nullable<DocumentFontSize>();
					if (currentResolvedStyle.color						== resolvedStyle.color)						run->style->color =				Nullable<Color>();
					if (currentResolvedStyle.backgroundColor			== resolvedStyle.backgroundColor)			run->style->backgroundColor =	Nullable<Color>();
					if (currentResolvedStyle.style.bold					== resolvedStyle.style.bold)				run->style->bold =				Nullable<bool>();
					if (currentResolvedStyle.style.italic				== resolvedStyle.style.italic)				run->style->italic =			Nullable<bool>();
					if (currentResolvedStyle.style.underline			== resolvedStyle.style.underline)			run->style->underline =			Nullable<bool>();
					if (currentResolvedStyle.style.strikeline			== resolvedStyle.style.strikeline)			run->style->strikeline =		Nullable<bool>();
					if (currentResolvedStyle.style.antialias			== resolvedStyle.style.antialias)			run->style->antialias =			Nullable<bool>();
					if (currentResolvedStyle.style.verticalAntialias	== resolvedStyle.style.verticalAntialias)	run->style->verticalAntialias =	Nullable<bool>();

					if (run->style->face)				goto CONTINUE_PROCESSING;
					if (run->style->size)				goto CONTINUE_PROCESSING;
					if (run->style->color)				goto CONTINUE_PROCESSING;
					if (run->style->backgroundColor)	goto CONTINUE_PROCESSING;
					if (run->style->bold)				goto CONTINUE_PROCESSING;
					if (run->style->italic)				goto CONTINUE_PROCESSING;
					if (run->style->underline)			goto CONTINUE_PROCESSING;
					if (run->style->strikeline)			goto CONTINUE_PROCESSING;
					if (run->style->antialias)			goto CONTINUE_PROCESSING;
					if (run->style->verticalAntialias)	goto CONTINUE_PROCESSING;
					CopyFrom(replacedRuns, run->runs);
					return;

				CONTINUE_PROCESSING:
					if (From(run->runs).Cast<DocumentStylePropertiesRun>().First(nullptr) != nullptr)
					{
						FOREACH(Ptr<DocumentRun>, subRun, run->runs)
						{
							if (auto styleRun = subRun.Cast<DocumentStylePropertiesRun>())
							{
								DocumentModel::MergeStyle(styleRun->style, run->style);
								replacedRuns.Add(styleRun);
							}
							else
							{
								auto parentRun = CopyRun(run).Cast<DocumentStylePropertiesRun>();
								parentRun->runs.Add(subRun);
								replacedRuns.Add(parentRun);
							}
						}
						return;
					}

					resolvedStyles.Add(resolvedStyle);
					VisitContainer(run);
					resolvedStyles.RemoveAt(resolvedStyles.Count() - 1);
				}

				void Visit(DocumentStyleApplicationRun* run)override
				{
					const DocumentModel::ResolvedStyle& currentResolvedStyle = GetCurrentResolvedStyle();
					DocumentModel::ResolvedStyle resolvedStyle = model->GetStyle(run->styleName, currentResolvedStyle);
					resolvedStyles.Add(resolvedStyle);
					VisitContainer(run);
					resolvedStyles.RemoveAt(resolvedStyles.Count() - 1);
				}

				void Visit(DocumentHyperlinkRun* run)override
				{
					const DocumentModel::ResolvedStyle& currentResolvedStyle = GetCurrentResolvedStyle();
					DocumentModel::ResolvedStyle resolvedStyle = model->GetStyle(run->styleName, currentResolvedStyle);
					resolvedStyles.Add(resolvedStyle);
					VisitContainer(run);
					resolvedStyles.RemoveAt(resolvedStyles.Count() - 1);
				}

				void Visit(DocumentImageRun* run)override
				{
				}

				void Visit(DocumentEmbeddedObjectRun* run)override
				{
				}

				void Visit(DocumentParagraphRun* run)override
				{
					VisitContainer(run);
				}
			};
		}
		using namespace document_operation_visitors;

		namespace document_editor
		{
			void ClearUnnecessaryRun(DocumentParagraphRun* run, DocumentModel* model)
			{
				{
					ClearRunVisitor visitor;
					run->Accept(&visitor);
				}
				{
					CompressStyleRunVisitor visitor(model);
					run->Accept(&visitor);
				}
			}
		}
	}
}