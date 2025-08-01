#include "headers.h"
#include "box.h"

namespace renderer
{


	BoxBase::BoxBase(BoxBundle b)
		: _bundle(b)
	{
	}
	BoxBase::BoxBase(BoxBundle bundle, const BoxBase& parent)
	{
		_bundle = bundle;
		_parent = const_cast<BoxBase*>(&parent);
		if (_parent)
			_parent->_children.push_back(this);
	}

	void BoxBase::inherit(const BoxBase& parent)
	{
		_parent = const_cast<BoxBase*>(&parent);
		if (_parent)
			_parent->_children.push_back(this);
	}

	bool BoxBase::is_not_regular() const { return true; }



	void BoxBase::set_width(float width) { _bundle.width = width; }
	void BoxBase::set_height(float height) { _bundle.height = height; }
	float BoxBase::get_width() const { return _bundle.width; }
	float BoxBase::get_height() const { return _bundle.height; }
	void BoxBase::set_border(const Sides& border) { _bundle.border = border; }
	void BoxBase::set_padding(const Sides& padding) { _bundle.padding = padding; }
	void BoxBase::set_margin(const Sides& margin) { _bundle.margin = margin; }
	Sides BoxBase::get_border() const { return _bundle.border; }
	Sides BoxBase::get_padding() const { return _bundle.padding; }
	Sides BoxBase::get_margin() const { return _bundle.margin; }
	void BoxBase::set_top_left_position(const ImVec2& pos) { _bundle.topLeftPos = pos; }
	ImVec2 BoxBase::get_top_left_position() const {	return _bundle.topLeftPos; }
	void BoxBase::set_z_index(uint16_t zIndex) { _bundle.zIndex = zIndex; }
	uint16_t BoxBase::get_z_index() const { return _bundle.zIndex; }
	void BoxBase::set_display(DisplayType type) { _bundle.display = type; }
	DisplayType BoxBase::get_display() const { return _bundle.display; }
	void BoxBase::set_position_type(PositionType type) { _bundle.positionType = type; }
	PositionType BoxBase::get_position_type() const { return _bundle.positionType; }
	void BoxBase::set_align_items(AlignType align) { _bundle.alignItems = align; }
	const BoxBundle& BoxBase::get_bundle() const { return _bundle; }

	AlignType BoxBase::get_align_items() const { return _bundle.alignItems; }

	float BoxBase::get_content_width() const
	{
		return _bundle.width - _bundle.padding.left - _bundle.padding.right - _bundle.border.left - _bundle.border.right;
	}

	float BoxBase::get_content_height() const
	{
		return _bundle.height - _bundle.padding.top - _bundle.padding.bottom - _bundle.border.top - _bundle.border.bottom;
	}

	float BoxBase::get_total_width() const
	{
		return _bundle.width + _bundle.margin.left + _bundle.margin.right + _bundle.border.left + _bundle.border.right;
	}

	float BoxBase::get_total_height() const
	{
		return _bundle.height + _bundle.margin.top + _bundle.margin.bottom + _bundle.border.top + _bundle.border.bottom;
	}


	

}
