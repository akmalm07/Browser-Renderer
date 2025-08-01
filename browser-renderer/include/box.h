#pragma once

#include "config.h"
#include "units.h"
#include "vec_tools.h"

namespace renderer
{
	struct Sides
	{
	public:
		float left = 0.0f;
		float right = 0.0f;
		float top = 0.0f;
		float bottom = 0.0f;
		Sides() = default;
		Sides(float t, float r, float b, float l)
			: left(l), right(r), top(t), bottom(b) {
		}

		void set(float l, float r, float t, float b)
		{
			left = l;
			right = r;
			top = t;
			bottom = b;
		}
	};

	enum class BoxType
	{
		Regular,
		Image,
		Text,
		Link,
		Video,
		Audio,
		Canvas,
		Form,
		Div,

	};

	enum class DisplayType
	{
		None,
		Block,
		Inline,
		InlineBlock,
		Flex,
		Grid,
		Table,
		ListItem,
	};

	enum class AlignType
	{
		None,
		Left,
		Right,
		Center,
		Justify,
		Start,
		End,
	};

	enum class PositionType 
	{
		Static, 
		Relative,
		Absolute, 
		Fixed 
	};


	struct TextStyle
	{
		std::string fontFamily;
		float fontSize = 16.0;
		bool bold = false;
		bool italic = false;
		ImVec4 color = ImVec4(0, 0, 0, 1);
	};



	struct BoxConfigs
	{
		ImVec4 backgroundColor = { 1.0f, 1.0f, 1.0f, 1.0f };
		ImVec4 borderColor = { 0.0f, 0.0f, 0.0f, 1.0f };
		TextStyle textStyle;

		float opacity = 1.0f;
		float width = 0.0f;
		float height = 0.0f;
		float borderRadius = 0.0f;
		float borderWidth = 1.0f; 
		bool isVisible = true;

	};

	struct BoxBundle
	{
		float width = 0.0f;
		float height = 0.0f;

		Sides border;
		Sides padding;
		Sides margin;

		uint16_t zIndex = 0;

		BoxConfigs configs;

		DisplayType display = DisplayType::None;

		AlignType alignItems = AlignType::None;

		PositionType positionType = PositionType::Static;

		ImVec2 topLeftPos = { 0.0f, 0.0f };
	};

	
	class BoxBase
	{
	public:
		BoxBase() = default;
		BoxBase(BoxBundle bundle);
		BoxBase(BoxBundle bundle, const BoxBase& parent);
		BoxBase(const BoxBase&) = default;
		BoxBase& operator=(const BoxBase&) = default;
		BoxBase(BoxBase&&) = default;
		BoxBase& operator=(BoxBase&&) = default;

		void inherit(const BoxBase& parent);

		virtual bool is_not_regular() const;

		void set_width(float width);
		void set_height(float height);
		float get_width() const;
		float get_height() const;
		void set_border(const Sides& border);
		void set_padding(const Sides& padding);
		void set_margin(const Sides& margin);
		Sides get_border() const;
		Sides get_padding() const;
		Sides get_margin() const;
		void set_top_left_position(const ImVec2& pos);
		ImVec2 get_top_left_position() const;
		void set_z_index(uint16_t zIndex);
		uint16_t get_z_index() const;
		float get_content_width() const;
		float get_content_height() const;
		float get_total_width() const;
		float get_total_height() const;
		void set_display(DisplayType type);
		DisplayType get_display() const;
		void set_position_type(PositionType);
		PositionType get_position_type() const;
		AlignType get_align_items() const;
		void set_align_items(AlignType align);

		const BoxBundle& get_bundle() const;

		virtual ~BoxBase() = default;

	protected:

		BoxBundle _bundle;

		BoxBase* _parent = nullptr;

		std::vector<BoxBase*> _children;

		std::function<void(const BoxBundle&)> _onClick;
		std::function<void(const BoxBundle&)> _onHover;

	};

	template<BoxType T>
	class Box;

	template<>
	class Box<BoxType::Regular> : public BoxBase
	{
	public:
		Box() = default;

		Box(BoxBundle bundle)
			: BoxBase(bundle) {
		}
	};

	template<>
	class Box<BoxType::Image> : public BoxBase
	{
	public:
		Box() = default;

		Box(BoxBundle bundle, const std::filesystem::path& url)
			: BoxBase(bundle), _imgUrl(url) {
		}

		bool is_not_regular() const override { return true; };

		const std::filesystem::path& get_image_url() const { return _imgUrl; }
		void set_image_url(const std::filesystem::path& url) { _imgUrl = url; }
	private:
		std::filesystem::path _imgUrl; 
	};

	template<>
	class Box<BoxType::Text> : public BoxBase
	{
	public:
		Box() = default;
		
		Box(BoxBundle bundle, const std::string& text)
			: BoxBase(bundle), _text(text) {
		}

		bool is_not_regular() const override { return true; };

		const std::string& get_text() const { return _text; }
		void set_text(const std::string& text) { _text = text; }

	private:
		std::string _text;
	};

	template<>
	class Box<BoxType::Link> : public BoxBase
	{
	public:
		Box() = default;
		
		Box(BoxBundle bundle, const std::string& url)
			: BoxBase(bundle), _url(url) {
		}

		bool is_not_regular() const override { return true; };

		const std::string& get_url() const { return _url; }
		void set_url(const std::string& url) { _url = url; }
	private:
		std::string _url;
	};

	template<>
	class Box<BoxType::Video> : public BoxBase
	{
	public:
		Box() = default;
		
		Box(BoxBundle bundle, const std::filesystem::path& videoUrl, bool isPlaying, bool isLooping, bool isMuted, float volume)
			: BoxBase(bundle), _videoUrl(videoUrl), _isPlaying(isPlaying), _isLooping(isLooping), _isMuted(isMuted), _volume(clamp(volume, 0.0f, 1.0f)) {
		}

		bool is_not_regular() const override { return true; };

		const std::filesystem::path& get_video_url() const { return _videoUrl; }
		void set_video_url(const std::filesystem::path& url) { _videoUrl = url; }

	private:
		std::filesystem::path _videoUrl;
		bool _isPlaying = false;
		bool _isLooping = false;
		bool _isMuted = false;
		float _volume = 1.0f; 
	};

	template<>
	class Box<BoxType::Audio> : public BoxBase
	{
	public:
		Box() = default;

		Box(BoxBundle bundle, const std::filesystem::path& audioUrl, bool isPlaying, bool isLooping, bool isMuted, float volume)
			: BoxBase(bundle), _audioUrl(audioUrl), _isPlaying(isPlaying), _isLooping(isLooping), _isMuted(isMuted), _volume(clamp(volume, 0.0f, 1.0f)) {
		}

		bool is_not_regular() const override { return true; };

		const std::filesystem::path& get_audio_url() const { return _audioUrl; }
		void set_audio_url(const std::filesystem::path& url) { _audioUrl = url; }
	private:
		std::filesystem::path _audioUrl;
		bool _isPlaying = false;
		bool _isLooping = false;
		bool _isMuted = false;
		float _volume = 1.0f;
	};


	template<>
	class Box<BoxType::Canvas> : public BoxBase
	{
	public:
		Box() = default;
		Box(BoxBundle bundle, const std::string& canvasId)
			: BoxBase(bundle), _canvasId(canvasId) {
		}

		bool is_not_regular() const override { return true; };

		const std::string& get_canvas_id() const { return _canvasId; }
		void set_canvas_id(const std::string& id) { _canvasId = id; }
	private:
		std::string _canvasId;
	};
	
}