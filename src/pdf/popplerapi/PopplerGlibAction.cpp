#include "PopplerGlibAction.h"

PopplerGlibAction::PopplerGlibAction(PopplerAction* action, PopplerDocument* document)
 : action(action),
   document(document)
{
    XOJ_INIT_TYPE(PopplerGlibAction);
   	g_object_ref(document);
}

PopplerGlibAction::~PopplerGlibAction()
{
	XOJ_CHECK_TYPE(PopplerGlibAction);

	poppler_action_free(action);
	action = NULL;

	if (document)
	{
		g_object_unref(document);
	    document = NULL;
	}

    XOJ_RELEASE_TYPE(PopplerGlibAction);
}

XojLinkDest* PopplerGlibAction::getDestination()
{
	XOJ_CHECK_TYPE(PopplerGlibAction);

	XojLinkDest* dest = link_dest_new();
	dest->dest = new LinkDestination();
	dest->dest->setName(getTitle());

	// every other action is not supported in Xournal
	if (action->type == POPPLER_ACTION_GOTO_DEST)
	{
		PopplerActionGotoDest* actionDest = (PopplerActionGotoDest*)action;
		PopplerDest* pDest = actionDest->dest;

		if (pDest == NULL)
		{
			return dest;
		}

		linkFromDest(dest->dest, pDest);
	}

	return dest;
}

void PopplerGlibAction::linkFromDest(LinkDestination* link, PopplerDest* pDest)
{
	XOJ_CHECK_TYPE(PopplerGlibAction);

	switch(pDest->type)
	{
	case POPPLER_DEST_UNKNOWN:
		g_warning("PDF Contains unknown link destination");
		break;
	case POPPLER_DEST_XYZ:
		{
			PopplerPage* page = poppler_document_get_page(document, pDest->page_num);
			if (page == NULL)
			{
				return;
			}

			double pageWidth = 0;
			double pageHeight = 0;
			poppler_page_get_size(page, &pageWidth, &pageHeight);

			if (pDest->left)
			{
				link->setChangeLeft(pDest->left);
			}
			else if (pDest->right)
			{
				link->setChangeLeft(pageWidth - pDest->right);
			}

			if (pDest->top)
			{
				link->setChangeTop(pageHeight - MIN(pageHeight, pDest->top));
			}
			else if (pDest->bottom)
			{
				link->setChangeTop(pageHeight - MIN(pageHeight, pageHeight - pDest->bottom));
			}

			if (pDest->zoom != 0)
			{
				link->setChangeZoom(pDest->zoom);
			}

			g_object_unref(page);
		}
		break;
	case POPPLER_DEST_FIT:
		g_warning("Unimplemented link type: POPPLER_DEST_FIT");
		break;
	case POPPLER_DEST_FITH:
		g_warning("Unimplemented link type: POPPLER_DEST_FITH");
		break;
	case POPPLER_DEST_FITV:
		g_warning("Unimplemented link type: POPPLER_DEST_FITV");
		break;
	case POPPLER_DEST_FITR:
		g_warning("Unimplemented link type: POPPLER_DEST_FITR");
		break;
	case POPPLER_DEST_FITB:
		g_warning("Unimplemented link type: POPPLER_DEST_FITB");
		break;
	case POPPLER_DEST_FITBH:
		g_warning("Unimplemented link type: POPPLER_DEST_FITBH");
		break;
	case POPPLER_DEST_FITBV:
		g_warning("Unimplemented link type: POPPLER_DEST_FITBV");
		break;
	case POPPLER_DEST_NAMED:
		{
			PopplerDest* pDest2 = poppler_document_find_dest(document, pDest->named_dest);
			if (pDest2 != NULL)
			{
				linkFromDest(link, pDest2);
				poppler_dest_free(pDest2);
				return;
			}
		}
		break;

	default:
		break;
	}

	link->setPdfPage(pDest->page_num - 1);
}

string PopplerGlibAction::getTitle()
{
	XOJ_CHECK_TYPE(PopplerGlibAction);

	return ((PopplerActionAny*)action)->title;
}
